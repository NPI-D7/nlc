#pragma once

#include <nuseful/json.hpp>
#include <string>

namespace nlc {
namespace lang {

std::string get(const std::string &key);

void load(const std::string &lang);
} // namespace lang
} // namespace nlc