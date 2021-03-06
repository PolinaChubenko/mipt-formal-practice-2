#pragma once

#include "ContextFreeGrammar.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>


class Earley {
protected:
    struct Situation {
        Rule rule;
        size_t word_pos = 0;
        bool is_complete_done = false;
    public:
        Situation() = default;
        Situation(char, std::string, size_t, size_t);
        Situation(const std::string&, size_t, size_t);
        explicit Situation(const std::string& rule);
    };
    struct Comparator {
        bool operator() (const Situation&, const Situation&) const;
    };
protected:
    ContextFreeGrammar grammar;
    std::vector<std::set<Situation, Comparator>> situations; // aka D
protected:
    void scan(size_t, const std::string&);
    bool complete(size_t);
    bool predict(size_t);
public:
    Earley() = default;
    explicit Earley(size_t);
    explicit Earley(ContextFreeGrammar);
    explicit Earley(const std::vector<std::string>&);
    void set_grammar(const ContextFreeGrammar&);
    friend std::istream& operator >> (std::istream&, Earley&);
    friend std::ostream& operator << (std::ostream&, const Earley&);
    bool parse(const std::string&);
};

