/*
 *  This file is part of SUT Editor Plugin for AppCreator based application.
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

#include <dsleditor/dsloutlinemodel.hpp>

namespace model{ namespace ts{
class SutItem;
}}

namespace suteditor {

class SutOutlineModel
    : public dsleditor::DslOutlineModel
{
  friend class ComBuildSutOutlineModel;

public:
  SutOutlineModel(QObject* parent = 0);
  virtual ~SutOutlineModel();

public:
  model::ts::SutItem*  sutModel();

public:
  virtual void reset();

private:
  Q_DISABLE_COPY(SutOutlineModel)
  class Private;
  Private* _d;
};

} // namespace suteditor
