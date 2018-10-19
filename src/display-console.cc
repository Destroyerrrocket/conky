/*
 *
 * Conky, a system monitor, based on torsmo
 *
 * Please see COPYING for details
 *
 * Copyright (C) 2018 François Revol et al.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <config.h>

#include "conky.h"
#include "nc.h"
#include "display-console.hh"

#include <iostream>
#include <sstream>
#include <unordered_map>

static conky::simple_config_setting<bool> extra_newline("extra_newline", false,
                                                        false);

namespace conky {
namespace {

conky::display_output_console console_output("console");

}  // namespace

namespace priv {


}  // namespace priv

display_output_console::display_output_console(const std::string &name_)
    : display_output_base(name_) {
  // lowest priority, it's a fallback
  priority = 0;
}

bool display_output_console::detect() {
  if ((out_to_stdout.get(*state) || out_to_stderr.get(*state)) && !out_to_ncurses.get(*state)) {
    std::cerr << "Display output '" << name << "' enabled in config." << std::endl;
    return true;
  }
  return false;
}

bool display_output_console::initialize() {
  return true;
}

bool display_output_console::shutdown() {
  return true;
}

void display_output_console::draw_string(const char *s, int w) {
  if (out_to_stdout.get(*state)) {
    printf("%s\n", s);
    if (extra_newline.get(*state)) { fputc('\n', stdout); }
    fflush(stdout); /* output immediately, don't buffer */
  }
  if (out_to_stderr.get(*state)) {
    fprintf(stderr, "%s\n", s);
    fflush(stderr); /* output immediately, don't buffer */
  }
}

}  // namespace conky

