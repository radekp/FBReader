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

#include "ZLOptions.h"
#include "ZLOptions_internal.h"

ZLOptions *ZLOptions::ourInstance = 0;

ZLOption::ZLOption(const std::string &group, const std::string &optionName) {
	myGroup = group;
	myOptionName = optionName;
	myIsSynchronized = false;
}

ZLOption::~ZLOption() {
}

ZLBooleanOption::ZLBooleanOption(const std::string &group, const std::string &optionName, bool defaultValue) : ZLOption(group, optionName) {
	myDefaultValue = defaultValue;
}

bool ZLBooleanOption::value() const {
	if (!myIsSynchronized) {
		ZLOptions::instance().setGroup(myGroup);
		myValue = ZLOptions::instance().booleanValue(myOptionName, myDefaultValue);
		myIsSynchronized = true;
	}
	return myValue;
}

void ZLBooleanOption::setValue(bool value) const {
	if (myIsSynchronized && (myValue == value)) {
		return;
	}
	myValue = value;
	myIsSynchronized = true;
	ZLOptions::instance().setGroup(myGroup);
	if (myValue == myDefaultValue) {
		ZLOptions::instance().unsetValue(myOptionName);
	} else {
		ZLOptions::instance().setValue(myOptionName, myValue);
	}
}

ZLBoolean3Option::ZLBoolean3Option(const std::string &group, const std::string &optionName, Boolean3 defaultValue) : ZLOption(group, optionName) {
	myDefaultValue = defaultValue;
}

Boolean3 ZLBoolean3Option::value() const {
	if (!myIsSynchronized) {
		ZLOptions::instance().setGroup(myGroup);
		myValue = (Boolean3)ZLOptions::instance().integerValue(myOptionName, myDefaultValue);
		myIsSynchronized = true;
	}
	return myValue;
}

void ZLBoolean3Option::setValue(Boolean3 value) const {
	if (myIsSynchronized && (myValue == value)) {
		return;
	}
	myValue = value;
	myIsSynchronized = true;
	ZLOptions::instance().setGroup(myGroup);
	if (myValue == myDefaultValue) {
		ZLOptions::instance().unsetValue(myOptionName);
	} else {
		ZLOptions::instance().setValue(myOptionName, myValue);
	}
}

ZLColorOption::ZLColorOption(const std::string &group, const std::string &optionName, ZLColor defaultValue) : ZLOption(group, optionName) {
	myDefaultIntValue = defaultValue.intValue();
}

ZLColor ZLColorOption::value() const {
	if (!myIsSynchronized) {
		ZLOptions::instance().setGroup(myGroup);
		myIntValue = ZLOptions::instance().integerValue(myOptionName, myDefaultIntValue);
		myIsSynchronized = true;
	}
	return ZLColor(myIntValue);
}

void ZLColorOption::setValue(ZLColor value) const {
	if (myIsSynchronized && (myIntValue == value.intValue())) {
		return;
	}
	myIntValue = value.intValue();
	myIsSynchronized = true;
	ZLOptions::instance().setGroup(myGroup);
	if (myIntValue == myDefaultIntValue) {
		ZLOptions::instance().unsetValue(myOptionName);
	} else {
		ZLOptions::instance().setValue(myOptionName, myIntValue);
	}
}

ZLIntegerOption::ZLIntegerOption(const std::string &group, const std::string &optionName, int defaultValue) : ZLOption(group, optionName) {
	myDefaultValue = defaultValue;
}

int ZLIntegerOption::value() const {
	if (!myIsSynchronized) {
		ZLOptions::instance().setGroup(myGroup);
		myValue = ZLOptions::instance().integerValue(myOptionName, myDefaultValue);
		myIsSynchronized = true;
	}
	return myValue;
}

void ZLIntegerOption::setValue(int value) const {
	if (myIsSynchronized && (myValue == value)) {
		return;
	}
	myValue = value;
	myIsSynchronized = true;
	ZLOptions::instance().setGroup(myGroup);
	if (myValue == myDefaultValue) {
		ZLOptions::instance().unsetValue(myOptionName);
	} else {
		ZLOptions::instance().setValue(myOptionName, myValue);
	}
}

ZLDoubleOption::ZLDoubleOption(const std::string &group, const std::string &optionName, double defaultValue) : ZLOption(group, optionName) {
	myDefaultValue = defaultValue;
}

double ZLDoubleOption::value() const {
	if (!myIsSynchronized) {
		ZLOptions::instance().setGroup(myGroup);
		myValue = ZLOptions::instance().doubleValue(myOptionName, myDefaultValue);
		myIsSynchronized = true;
	}
	return myValue;
}

void ZLDoubleOption::setValue(double value) const {
	if (myIsSynchronized && (myValue == value)) {
		return;
	}
	myValue = value;
	myIsSynchronized = true;
	ZLOptions::instance().setGroup(myGroup);
	if (myValue == myDefaultValue) {
		ZLOptions::instance().unsetValue(myOptionName);
	} else {
		ZLOptions::instance().setValue(myOptionName, myValue);
	}
}

ZLStringOption::ZLStringOption(const std::string &group, const std::string &optionName, const std::string &defaultValue) : ZLOption(group, optionName){
	myDefaultValue = defaultValue;
}

const std::string ZLStringOption::value() const {
	if (!myIsSynchronized) {
		ZLOptions::instance().setGroup(myGroup);
		myValue = ZLOptions::instance().stringValue(myOptionName, myDefaultValue);
		myIsSynchronized = true;
	}
	return myValue;
}

void ZLStringOption::setValue(const std::string &value) const {
	if (myIsSynchronized && (myValue == value)) {
		return;
	}
	myValue = value;
	myIsSynchronized = true;
	ZLOptions::instance().setGroup(myGroup);
	if (myValue == myDefaultValue) {
		ZLOptions::instance().unsetValue(myOptionName);
	} else {
		ZLOptions::instance().setValue(myOptionName, myValue);
	}
}
