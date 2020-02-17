/*
 *  This file is part of Test Case Editor Plugin for AppCreator based application.
 *
 *  Copyright (C) 2013 Jan Krause <jan.krause.no19@gmail.com>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
*/

#pragma once

#include <QtGlobal>

namespace testcaseeditor {
namespace Constants {

static const char TESTCASEEDITOR_CONTEXT[]  = "Test Case Editor";
static const char	TESTCASEEDITOR_NAME[]     = "test case editor";
static const char	TESTCASEEDITOR_ID[]       = "TestCaseEditor";
static const char	TESTCASE_MIME_TYPE[]      = "application/testcase";

static const char	TESTCASEGRAPHIC_NAME[] = "test case graphic";
static const char	TESTCASEGRAPHIC_ID[] = "TestCaseGraphic";
static const char	TESTCASEGRAPHIC_MIME_TYPE[] = "application/testcasegraphic";

// Languages
static const char LANG_TESTCASE[]           = "LANG_TESTCASE";

// Settings page
const char TESTCASE_SETTINGS_CATEGORY[]  = "T.TstcaseEditor";
const char TESTCASE_SETTINGS_TR_CATEGORY[] = QT_TRANSLATE_NOOP("TestcaseEditor", "Testcase Editor");
const char TESTCASE_SETTINGS_CATEGORY_ICON[]  = ":/mobata/images/ts/manytestcase.png";
const char TESTCASE_SETTINGS_ID[] = "A.TestcaseEditor";

} // namespace testcaseeditor
} // namespace Constants
