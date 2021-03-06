/**
 * Copyright (c) 2011-2015 libgroestlcoin developers (see AUTHORS)
 *
 * This file is part of libgroestlcoin-explorer.
 *
 * libgroestlcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <groestlcoin/explorer/primitives/language.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <groestlcoin/groestlcoin.hpp>
#include <groestlcoin/explorer/define.hpp>

using namespace po;

namespace libgroestlcoin {
namespace explorer {
namespace primitives {

// DRY
static const char* language_en = "en";
static const char* language_es = "es";
static const char* language_ja = "ja";
static const char* language_zh_Hans = "zh_Hans";
static const char* language_zh_Hant = "zh_Hant";
static const char* language_any = "any";

language::language()
    : value_(bc::language::all)
{
}

language::language(const std::string& token)
{
    std::stringstream(token) >> *this;
}

language::language(dictionary_list& languages)
    : value_(languages)
{
}

language::language(const language& other)
    : value_(other.value_)
{
}

language::operator const bc::dictionary_list&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, language& argument)
{
    std::string text;
    input >> text;

    argument.value_.clear();

    if (text == language_any)
        argument.value_.assign(bc::language::all.begin(),
            bc::language::all.end());
    else if(text == language_en)
        argument.value_.push_back(&bc::language::en);
    else if (text == language_es)
        argument.value_.push_back(&bc::language::es);
    else if (text == language_ja)
        argument.value_.push_back(&bc::language::ja);
    else if (text == language_zh_Hans)
        argument.value_.push_back(&bc::language::zh_Hans);
    else if (text == language_zh_Hant)
        argument.value_.push_back(&bc::language::zh_Hant);
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const language& argument)
{
    std::string text;

    if (argument.value_.size() > 1)
        text = language_any;
    else if(argument.value_.front() == &bc::language::en)
        text = language_en;
    else if (argument.value_.front() == &bc::language::es)
        text = language_es;
    else if (argument.value_.front() == &bc::language::ja)
        text = language_ja;
    else if (argument.value_.front() == &bc::language::zh_Hans)
        text = language_zh_Hans;
    else if (argument.value_.front() == &bc::language::zh_Hant)
        text = language_zh_Hant;
    else
    {
        BITCOIN_ASSERT_MSG(false, "Unexpected encoding value.");
    }

    output << text;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libgroestlcoin
