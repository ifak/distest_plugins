/*
 *  This file is part of Spenat Plugin for Spenat Creator.
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
#ifndef DISTESTEDITOR_GLOBAL_HPP
#define DISTESTEDITOR_GLOBAL_HPP

#include <qglobal.h>

#if defined(DISTESTEDITOR_LIBRARY)
#  define DISTESTEDITOR_EXPORT Q_DECL_EXPORT
#else
#  define DISTESTEDITOR_EXPORT Q_DECL_IMPORT
#endif



#endif // DISTESTEDITOR_GLOBAL_HPP
