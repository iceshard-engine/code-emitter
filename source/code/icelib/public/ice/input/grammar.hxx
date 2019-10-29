#pragma once
#include <ice/input/token_type.hxx>
#include <ice/input/tokenizer.hxx>
#include <string>
#include <vector>
#include <memory>
#include <variant>

namespace ice::input::grammar
{

    template<class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    template<class... Ts>
    overloaded(Ts...)->overloaded<Ts...>;

    struct RuleType
    {
        TokenType token;

        bool optional = false;
    };

    struct RuleValue
    {
        TokenType token;

        std::string value;

        bool optional = false;
    };

    struct Group;

    struct RuleGroup
    {
        RuleGroup(Group group) noexcept;

        std::unique_ptr<Group> group;

        bool optional = false;
    };

    struct Group
    {
        std::string name;

        std::vector<token> matched_tokens;

        std::vector<std::variant<RuleType, RuleValue>> rules;

        bool match(size_t& index, std::vector<token>& tokens, Tokenizer& tokenizer)
        {
            matched_tokens.clear();

            auto const start_index = index;
            auto size = tokens.size();

            auto has_next_token = [&]() noexcept->bool
            {
                return index < size || tokenizer.has_next_token();
            };

            auto next_token = [&]() noexcept->token
            {
                if (index == size)
                {
                    tokens.emplace_back(tokenizer.next_token());
                    ++size;
                }
                return tokens[index];
            };

            auto rule_it = rules.begin();
            auto const rule_end = rules.end();

            bool matched = true;
            for (; matched && rule_it != rule_end && has_next_token(); ++rule_it)
            {
                auto parsed_token = next_token();

                std::visit(
                    overloaded{
                        [&](RuleType const& arg) {
                            matched &= (arg.token == parsed_token.type);
                            if (matched)
                            {
                                ++index;
                            }
                            else
                            {
                                matched |= arg.optional;
                            }
                        },
                        [&](RuleValue const& arg) {
                            matched &= ((arg.token == parsed_token.type) && (arg.value == parsed_token.value));
                            if (matched)
                            {
                                ++index;
                            }
                            else
                            {
                                matched |= arg.optional;
                            }
                        },
                    },
                    *rule_it);
            }

            if (rule_it != rule_end || matched == false)
            {
                index = start_index;
            }
            else
            {
                for (auto i = start_index; i < index; ++i)
                {
                    matched_tokens.emplace_back(tokens[i]);
                }
            }

            return matched && rule_it == rule_end;
        }

        bool match(std::vector<token>& tokens, Tokenizer& tokenizer)
        {
            matched_tokens.clear();

            auto it = tokens.begin();
            auto const end = tokens.end();

            auto has_next_token = [&]() noexcept->bool
            {
                return it != end || tokenizer.has_next_token();
            };

            auto next_token = [&]() noexcept->token
            {
                return it != end ? *it++ : tokenizer.next_token();
            };

            auto rule_it = rules.begin();
            auto const rule_end = rules.end();

            bool matched = true;
            for (; matched && rule_it != rule_end && has_next_token(); ++rule_it)
            {
                auto parsed_token = next_token();

                std::visit(
                    overloaded{
                        [&](RuleType const& arg) {
                            matched &= (arg.token == parsed_token.type) || arg.optional;
                        },
                        [&](RuleValue const& arg) {
                            matched &= ((arg.token == parsed_token.type) && (arg.value == parsed_token.value)) || arg.optional;
                        },
                    },
                    *rule_it);

                matched_tokens.push_back(std::move(parsed_token));
            }

            if (rule_it != rule_end || matched == false)
            {
                tokens = std::move(matched_tokens);
            }

            return matched && rule_it == rule_end;
        }
    };

    RuleGroup::RuleGroup(Group group) noexcept
        : group(std::make_unique<Group>(std::move(group)))
    {
    }

    class Grammar final
    {
    public:
        Grammar() noexcept = default;
        ~Grammar() noexcept = default;

        void add(Group group) noexcept
        {
            _groups.push_back(std::move(group));
        }

        bool parse(Tokenizer& tokenizer)
        {
            bool matched = false;

            std::vector<token> tokens_temp;
            for (auto& group : _groups)
            {
                size_t index = 0;
                if (group.match(index, tokens_temp, tokenizer))
                {
                    matched |= true;
                }
            }

            return matched;
        }

        void print()
        {
            for (auto& group : _groups)
            {
                if (group.matched_tokens.empty() == false)
                {
                    fmt::print("Group matched: {}\n", group.name);
                    for (auto const& token : group.matched_tokens)
                    {
                        fmt::print("{},", token);
                    }
                    fmt::print("\n");
                }
            }
        }

    private:
        std::vector<Group> _groups;
    };

} // namespace ice::input::grammar
