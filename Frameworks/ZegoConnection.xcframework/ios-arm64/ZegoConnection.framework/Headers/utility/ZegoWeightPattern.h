#ifndef ZegoWeightPattern_h
#define ZegoWeightPattern_h
#include <algorithm>
#include <string>
#include <vector>
namespace ZEGO {
namespace BASE {
/* 集合权重类实现 
功能如下：
       指定N个包含不重复数据的集合(集合间数据也不重复)，指定每个集合的权重。 生成按权重集合的数据列表
注意：
     1、模板类型 T 可以是基础类型，或者类类型。类类型 必须重载实现T == 操作符。 后续的增，变，查需要使用

使用如下:
       指定N个数据不重复集合例如：set_a={data1, data2}, set_b={data3,data4}, set_c={data5,data6}; 
       指定N个集合各个集合的权重； set_a.weight = 3, set_b.weight = 2, set_c.weight = 1
       则可以通过 一直调用 GetNextWeightData 可按集合的权重比，拿到data 数据. 
       获取数据后若是不调用MarkPatternData ， 则再次调用GetNextWeightData 拿到的还是上次的数据
*/

template <typename T> struct PatternData {
    T user_data;
    bool used = false;
    int used_count = 0; //被选中的次数
};

template <typename T> struct PatternDataSet {
    std::vector<PatternData<T>> pattern_data_list;
    std::string set_name;   //集合名称
    int weight = 0;         //没获取后mark一次就 -1
    int src_weight = 0;     //集合权重值，为设置的值，一直不变
    int set_used_count = 0; //集合被选中的次数
};

#define WeightContextInvaild -1

typedef int WeightContext;

template <typename T> class CWeightPattern {
  public:
    CWeightPattern() {}
    ~CWeightPattern() {}

    void CreatePattern(std::vector<PatternDataSet<T>> &&pattern_data_set_list) {
        if (pattern_data_set_list.empty()) {
            assert(false);
            return;
        }

        DestroyPattern();

        m_next_pattern_set_index = 0;
        m_pattern_data_set_list = std::move(pattern_data_set_list);
    }

    void DestroyPattern() {
        m_pattern_data_set_list.clear();
        m_next_pattern_set_index = 0;
    }

    std::vector<PatternDataSet<T>> GetPattern() { return m_pattern_data_set_list; }

    //get next weight data, but not mark used, if you used used must call MarkPatternData. and next will get right data
    WeightContext GetNextWeightData(T &pattern_data, std::string &out_set_name) {
        int pattern_set_list_size = (int)m_pattern_data_set_list.size();
        if (pattern_set_list_size == 0) {
            return WeightContextInvaild;
        }

        //check next pattern_set index is invalid ?
        if (m_next_pattern_set_index < 0 || m_next_pattern_set_index >= pattern_set_list_size) {
            m_next_pattern_set_index = 0;
        }

        //find next have weight
        int have_weight_index = FindSetHaveWeight(m_next_pattern_set_index);
        if (-1 == have_weight_index) {
            m_next_pattern_set_index = 0; //not find index reset
            ResetAllSetWeight();
            have_weight_index = FindSetHaveWeight(m_next_pattern_set_index);
        }

        if (-1 == have_weight_index) {
            assert(false);
            return WeightContextInvaild; //impossible
        }

        auto &pattern_data_set = m_pattern_data_set_list[have_weight_index];
        if (!HaveUnusedDataInSet(pattern_data_set)) {
            ResetSetPatternDataToUnused(pattern_data_set);
        }

        FindUnusedDataInSet(pattern_data_set, pattern_data, out_set_name);

        return have_weight_index;
    }

    void MarkPatternData(WeightContext context, const T &target_pattern_data) {
        int have_weight_index = context;
        int pattern_set_list_size = (int)m_pattern_data_set_list.size();

        if (have_weight_index < 0 || have_weight_index >= pattern_set_list_size) {
            assert(false);
            return;
        }

        auto &pattern_data_set = m_pattern_data_set_list[have_weight_index];
        MarkDataUsedInSet(pattern_data_set, target_pattern_data);
        pattern_data_set.set_used_count++;

        pattern_data_set.weight--;
        if (pattern_data_set.weight < 0)
            pattern_data_set.weight = 0;

        have_weight_index++;
        m_next_pattern_set_index = have_weight_index;
        if (m_next_pattern_set_index >= pattern_set_list_size)
            m_next_pattern_set_index = 0;
    }

    bool FindPatternData(const T &src, T &out, std::string &set_name) {
        for (const auto &pattern_set : m_pattern_data_set_list) {
            for (const auto &pattern_data : pattern_set.pattern_data_list) {
                if (pattern_data.user_data == src) {
                    out = pattern_data.user_data;
                    set_name = pattern_set.set_name;
                    return true;
                }
            }
        }
        return false;
    }

    bool UpdatePatternData(const T &src) {
        for (auto &pattern_set : m_pattern_data_set_list) {
            for (auto &pattern_data : pattern_set.pattern_data_list) {
                if (pattern_data.user_data == src) {
                    pattern_data.user_data = src;
                    return true;
                }
            }
        }
        return false;
    }

    //move data to set back
    bool MoveDataToPatternDataSetBack(const T &user_data) {
        for (int i = 0; i < (int)m_pattern_data_set_list.size(); i++) {
            auto &pattern_set = m_pattern_data_set_list[i];
            int index = -1;
            for (int j = 0; j < pattern_set.pattern_data_list.size(); j++) {
                if (pattern_set.pattern_data_list[j].user_data == user_data) {
                    index = j;
                    break;
                }
            }

            if (index >= 0) {
                std::rotate(pattern_set.pattern_data_list.begin() + index,
                            pattern_set.pattern_data_list.begin() + index + 1,
                            pattern_set.pattern_data_list.end());
                return true;
            }
        }
        return false;
    }

  private:
    void ResetAllSetWeight() {
        for (auto &pattern_set : m_pattern_data_set_list) {
            pattern_set.weight = pattern_set.src_weight;
        }
    }

    void MarkDataUsedInSet(PatternDataSet<T> &pattern_data_set, const T &target_pattern_data) {
        if (pattern_data_set.pattern_data_list.empty()) {
            assert(false);
            return;
        }

        for (auto &pattern_data : pattern_data_set.pattern_data_list) {
            if (pattern_data.user_data == target_pattern_data) {
                pattern_data.used = true;
                pattern_data.used_count++;
                return;
            }
        }

        assert(false);
        return;
    }

    void FindUnusedDataInSet(PatternDataSet<T> &pattern_data_set, T &out_pattern_data,
                             std::string &out_set_name) {
        if (pattern_data_set.pattern_data_list.empty()) {
            assert(false);
            return;
        }

        for (const auto &pattern_data : pattern_data_set.pattern_data_list) {
            if (!pattern_data.used) {
                out_pattern_data = pattern_data.user_data;
                out_set_name = pattern_data_set.set_name;
                return;
            }
        }
        assert(false);
        return;
    }

    bool HaveUnusedDataInSet(const PatternDataSet<T> &pattern_data_set) {
        for (const auto &pattern_data : pattern_data_set.pattern_data_list) {
            if (!pattern_data.used)
                return true;
        }

        return false;
    }

    void ResetSetPatternDataToUnused(PatternDataSet<T> &pattern_data_set) {
        for (auto &pattern_data : pattern_data_set.pattern_data_list) {
            pattern_data.used = false;
        }
    }

    int FindSetHaveWeight(int current_index) {
        int temp_current_index = current_index;
        int pattern_set_size = (int)m_pattern_data_set_list.size();
        if (temp_current_index < 0 || temp_current_index >= pattern_set_size)
            temp_current_index = 0;

        for (int i = 0; i < pattern_set_size; i++) {
            if (temp_current_index < 0 || temp_current_index >= pattern_set_size) {
                temp_current_index = 0;
            }

            auto &find_have_weight_set = m_pattern_data_set_list[temp_current_index];
            if (find_have_weight_set.weight > 0) {
                return temp_current_index;
            }

            temp_current_index++;
        }

        return -1;
    }

  private:
    int m_next_pattern_set_index = 0; //next group set index
    std::vector<PatternDataSet<T>> m_pattern_data_set_list;
};

} // namespace BASE
} // namespace ZEGO

#endif
