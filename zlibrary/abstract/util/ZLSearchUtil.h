/*
 * Copyright (C) 2005 Nikolay Pultsin <geometer@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __ZLSEARCHUTIL_H__
#define __ZLSEARCHUTIL_H__

#include <string>

class ZLSearchPattern {

public:
	ZLSearchPattern(const std::string &pattern, bool ignoreCase);
	int length() const { return myLowerCasePattern.length(); }

private:
	bool ignoreCase() const { return myIgnoreCase; }
	const std::string &lowerCasePattern() const { return myLowerCasePattern; }
	const std::string &upperCasePattern() const { return myUpperCasePattern; }

private:
	bool myIgnoreCase;
	std::string myLowerCasePattern;
	std::string myUpperCasePattern;

friend class ZLSearchUtil;
};

class ZLSearchUtil {

private:
	ZLSearchUtil();

public:
	static int find(const std::string &text, const ZLSearchPattern &pattern, int pos = 0);
};

#endif /* __ZLSEARCHUTIL_H__ */
