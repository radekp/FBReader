/*
 * FBReader -- electronic book reader
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

#include <abstract/ZLOptionsDialog.h>

#include "ColorOptionsPage.h"

#include "../view/PaintContext.h"
#include "../textview/TextView.h"

ColorOptionsPage::ColorOptionsPage(ZLOptionsDialogTab *dialogTab) {
	myComboEntry = new ComboOptionEntry(*this, "Color For", "Background");
	myComboEntry->addValue("Background");
	myComboEntry->addValue("Text");
	myComboEntry->addValue("Selected Text");
	myComboEntry->addValue("Tree Lines");
	myComboEntry->addValue("Position Indicator");

	dialogTab->addOptions(myComboEntry, 0);

	registerEntry(dialogTab,
		new ZLSimpleColorOptionEntry(PaintContext::BackgroundColorOption),
		myComboEntry->values()[0]
	);
	registerEntry(dialogTab,
		new ZLSimpleColorOptionEntry(PaintContext::TextColorOption),
		myComboEntry->values()[1]
	);
	registerEntry(dialogTab,
		new ZLSimpleColorOptionEntry(PaintContext::SelectedTextColorOption),
		myComboEntry->values()[2]
	);
	registerEntry(dialogTab,
		new ZLSimpleColorOptionEntry(TextView::TreeLinesColorOption),
		myComboEntry->values()[3]
	);
	registerEntry(dialogTab,
		new ZLSimpleColorOptionEntry(TextView::PositionIndicatorColorOption),
		myComboEntry->values()[4]
	);

	myComboEntry->onValueChange(myComboEntry->initialValue());
}
