# LibAnvil
# Copyright (C) 2012 - 2020 David Jolly
#
# LibAnvil is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# LibAnvil is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

DIR_BIN=../bin/
DIR_BIN_LIB=../bin/lib/
DIR_EXAMPLE=./
EXE=anvil
FLAGS=-march=native -std=c++0x -Wall -Werror
LIB=libanvil.a
LIB_FLAGS=-lboost_regex -lz

all: exe

### EXECUTABLE ###

exe:
	@echo ''
	@echo '--- BUILDING EXAMPLE -----------------------'
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(DIR_EXAMPLE)example.cpp $(DIR_BIN_LIB)$(LIB) -o $(DIR_BIN)$(EXE) $(LIB_FLAGS)
	@echo '--- DONE -----------------------------------'
