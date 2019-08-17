# LibAnvil
# Copyright (C) 2012 - 2019 David Jolly
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

BUILD_FLAGS_DBG=BUILD_FLAGS=-g
BUILD_FLAGS_REL=BUILD_FLAGS=-O3\ -DNDEBUG
DIR_BIN=./
DIR_BUILD=./build/
DIR_ROOT=./
DIR_SRC=./src/
JOB_SLOTS=4
LIB=libanvil.a

all: release

debug: begin_debug clean init lib_debug end

release: begin_release clean init lib_release end

### SETUP ###

begin_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBANVIL (DEBUG)'
	@echo '============================================'

begin_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBANVIL (RELEASE)'
	@echo '============================================'

clean:
	rm -f $(DIR_BIN)$(LIB)
	rm -rf $(DIR_BUILD)

end:
	@echo ''
	@echo '============================================'
	@echo 'BUILD DONE'
	@echo '============================================'
	@echo ''

init:
	mkdir -p $(DIR_BUILD)

### LIBRARY ###

lib_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBRARIES (DEBUG)'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_DBG) build -j$(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

lib_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBRARIES (RELEASE)'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_REL) build -j$(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

### MISC ###

lines:
	@echo ''
	@echo '============================================'
	@echo 'CALCULATING LINE COUNT'
	@echo '============================================'
	cloc $(DIR_ROOT)

static:
	@echo ''
	@echo '============================================'
	@echo 'RUNNING STATIC ANALYSIS'
	@echo '============================================'
	cppcheck --enable=all --std=c++11 $(DIR_SRC) $(DIR_TEST) $(DIR_TOOL)
