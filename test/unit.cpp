/*!
@file
@copyright The code is licensed under the MIT License
           <http://opensource.org/licenses/MIT>,
           Copyright (c) 2015 Niels Lohmann.
@author Niels Lohmann <http://nlohmann.me>
@see https://github.com/nlohmann/fifo_map
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define private public
#include "fifo_map.hpp"

using nlohmann::fifo_map;

#include <string>

/// helper function to check order of keys
std::string collect_keys(const fifo_map<std::string, int>& m)
{
    std::string result;
    for (auto x : m)
    {
        result += x.first;
    }
    return result;
}

TEST_CASE("element access")
{
    fifo_map<std::string, int> m = {{"C", 1}, {"A", 2}, {"B", 3}};
    const fifo_map<std::string, int> mc = m;

    SECTION("at")
    {
        CHECK(m.at("C") == 1);
        CHECK(m.at("A") == 2);
        CHECK(m.at("B") == 3);

        CHECK_THROWS_AS(m.at("Z"), std::out_of_range);

        CHECK(mc.at("C") == 1);
        CHECK(mc.at("A") == 2);
        CHECK(mc.at("B") == 3);

        CHECK_THROWS_AS(mc.at("Z"), std::out_of_range);
    }

    SECTION("operator[]")
    {
        CHECK(m["C"] == 1);
        CHECK(m["A"] == 2);
        CHECK(m["B"] == 3);

        CHECK_NOTHROW(m["Z"]);
        CHECK(m["Z"] == 0);
    }
}

TEST_CASE("iterators")
{
    fifo_map<std::string, int> m = {{"C", 1}, {"A", 2}, {"B", 3}};
    const fifo_map<std::string, int> mc = m;

    SECTION("begin/end with nonconst object")
    {
        fifo_map<std::string, int>::iterator it = m.begin();
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it == m.end());
    }

    SECTION("begin/end with const object")
    {
        fifo_map<std::string, int>::const_iterator it = mc.begin();
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it == mc.end());
    }

    SECTION("cbegin/cend with nonconst object")
    {
        fifo_map<std::string, int>::const_iterator it = m.cbegin();
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it == m.cend());
    }

    SECTION("cbegin/cend with const object")
    {
        fifo_map<std::string, int>::const_iterator it = mc.cbegin();
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it == mc.cend());
    }

    SECTION("begin/end with nonconst object")
    {
        fifo_map<std::string, int>::iterator it = m.begin();
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it == m.end());
    }

    SECTION("rbegin/rend with nonconst object")
    {
        fifo_map<std::string, int>::reverse_iterator it = m.rbegin();
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it == m.rend());
    }

    SECTION("rbegin/rend with const object")
    {
        fifo_map<std::string, int>::const_reverse_iterator it = mc.rbegin();
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it == mc.rend());
    }

    SECTION("crbegin/crend with nonconst object")
    {
        fifo_map<std::string, int>::const_reverse_iterator it = m.crbegin();
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it == m.crend());
    }

    SECTION("crbegin/crend with const object")
    {
        fifo_map<std::string, int>::const_reverse_iterator it = mc.crbegin();
        CHECK(it->first == "B");
        CHECK(it->second == 3);
        ++it;
        CHECK(it->first == "A");
        CHECK(it->second == 2);
        ++it;
        CHECK(it->first == "C");
        CHECK(it->second == 1);
        ++it;
        CHECK(it == mc.crend());
    }
}

TEST_CASE("capacity")
{
    nlohmann::fifo_map<std::string, int> m_empty;
    nlohmann::fifo_map<std::string, int> m_filled = {{"A", 1}, {"B", 2}};

    SECTION("empty")
    {
        CHECK(m_empty.empty());
        CHECK(! m_filled.empty());
    }

    SECTION("size")
    {
        CHECK(m_empty.size() == 0);
        CHECK(m_filled.size() == 2);
    }

    SECTION("max_size")
    {
        CHECK(m_empty.max_size() >= m_empty.size());
        CHECK(m_filled.max_size() >= m_filled.size());
    }
}

TEST_CASE("modifiers")
{
    nlohmann::fifo_map<std::string, int> m_empty;
    nlohmann::fifo_map<std::string, int> m_filled = {{"X", 1}, {"C", 2}};

    SECTION("clear")
    {
        CHECK(!m_filled.empty());
        CHECK(m_empty.empty());
        m_filled.clear();
        m_empty.clear();
        CHECK(m_filled.empty());
        CHECK(m_empty.empty());
    }

    SECTION("insert")
    {
        SECTION("insert value_type")
        {
            // check initial state
            CHECK(m_filled.size() == 2);
            CHECK(m_filled.m_keys.size() == 2);
            CHECK(collect_keys(m_filled) == "XC");

            // insert new value
            auto res1 = m_filled.insert({"A", 3});
            CHECK(m_filled["A"] == 3);
            CHECK(res1.second == true);
            CHECK(res1.first->first == "A");
            CHECK(res1.first->second == 3);

            // check that key and value way inserted
            CHECK(m_filled.size() == 3);
            CHECK(m_filled.m_keys.size() == 3);
            CHECK(collect_keys(m_filled) == "XCA");

            // insert already present value
            auto res2 = m_filled.insert({"A", 3});
            CHECK(m_filled["A"] == 3);
            CHECK(res2.second == false);
            CHECK(res2.first->first == "A");
            CHECK(res2.first->second == 3);

            // check that map remained unchanged
            CHECK(m_filled.size() == 3);
            CHECK(m_filled.m_keys.size() == 3);
            CHECK(collect_keys(m_filled) == "XCA");
        }
    }
}
