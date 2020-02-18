/*
 * This file is part of distest_plugins.
 *
 * distest_plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * distest_plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with distest_plugins.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DISTESTPROJECTCONSTANTS_HPP
#define DISTESTPROJECTCONSTANTS_HPP

namespace distestproject {
namespace Constants {

const char *const	PROJECTEDITOR_NAME = "DisTest project editor";
const char *const	PROJECTEDITOR_ID = "DisTest.DisTestProject";

const char *const PROJECTCONTEXT = "DisTestProject.ProjectContext";
const char *const LANG_DISTEST = "DISTEST";

// Actions:
const char ACTION_REPARSE_DISTESTPROJECT[] = "DisTestProject.Reparse";
const char ACTION_BUILD_CONTEXT[] = "DisTestProject.BuildCtx";
const char ACTION_BUILD[] = "DisTestProject.Build";
const char ACTION_BUILD_CLEAN[] = "DisTestProject.Build.Clean";
const char ACTION_ADDTESTCASE[] = "DisTestProject.AddTestCase";
const char ACTION_ADDPRIO[] = "DisTestProject.AddPrio";
const char ACTION_STARTTESTCASE[] = "DisTestProject.StartTestCase";

// Settings page
const char DISTEST_SETTINGS_CATEGORY[]  = "T.DisTest";
const char DISTEST_SETTINGS_TR_CATEGORY[] = QT_TRANSLATE_NOOP("DisTest", "Distributed Test");
const char DISTEST_SETTINGS_CATEGORY_ICON[]  = ":/core/images/filenew.png";
const char DISTEST_SUT_SETTINGS_ID[] = "A.DisTest.SUT";
const char DISTEST_TESTSYSTEM_SETTINGS_ID[] = "B.DisTest.TestSystem";
const char DISTEST_TESTCASE_SETTINGS_ID[] = "C.DisTest.TestCase";

//etc
const char DISTEST_SETTINGS_PREFIX[] = "DisTest";

//test report stuff
static const char TEST_REPORT_FOLDERNAME[] = "test report";
static const char	TESTREPORTGRAPHIC_NAME[] = "test report graphic";
static const char	TESTREPORTGRAPHIC_ID[] = "TestReportGraphic";
static const char	TESTREPORTGRAPHIC_MIME_TYPE[] = "application/testreportgraphic";

//attributeNames
const char FILENAME_ATTRIBUTE[] = "fileName";

} // namespace distestproject
} // namespace Constants

#endif // DISTESTPROJECTCONSTANTS_HPP
