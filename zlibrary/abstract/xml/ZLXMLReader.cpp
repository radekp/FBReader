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

#include <expat.h>
#include <string.h>

#include <abstract/ZLInputStream.h>

#include "ZLXMLReader.h"

static void fCharacterDataHandler(void *userData, const char *text, int len) {
	((ZLXMLReader*)userData)->characterDataHandler(text, len);
}

static void fStartElementHandler(void *userData, const char *name, const char **attributes) {
	((ZLXMLReader*)userData)->startElementHandler(((ZLXMLReader*)userData)->tag(name), attributes);
}

static void fEndElementHandler(void *userData, const char *name) {
	((ZLXMLReader*)userData)->endElementHandler(((ZLXMLReader*)userData)->tag(name));
}

static int cp1251[] = {
0x0402, 0x0403, 0x201A, 0x0453, 0x201E, 0x2026, 0x2020, 0x2021,
0x20AC, 0x2030, 0x0409, 0x2039, 0x040A, 0x040C, 0x040B, 0x040F,
0x0452, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
0xFFFD, 0x2122, 0x0459, 0x203A, 0x045A, 0x045C, 0x045B, 0x045F,
0x00A0, 0x040E, 0x045E, 0x0408, 0x00A4, 0x0490, 0x00A6, 0x00A7,
0x0401, 0x00A9, 0x0404, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0407,
0x00B0, 0x00B1, 0x0406, 0x0456, 0x0491, 0x00B5, 0x00B6, 0x00B7,
0x0451, 0x2116, 0x0454, 0x00BB, 0x0458, 0x0405, 0x0455, 0x0457,
0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417,
0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F,
0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427,
0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F,
0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437,
0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F,
0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447,
0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F};

static int cp1252[] = {
0x20AC, 0xFFFD, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0xFFFD, 0x017D, 0xFFFD,
0xFFFD, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0xFFFD, 0x017E, 0x0178,
0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7,
0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7,
0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7,
0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7,
0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7,
0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7,
0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF};

static int fUnknownEncodingHandler(void *, const XML_Char *name, XML_Encoding *info) {
	if (strcasecmp(name, "windows-1251") == 0) {
		for (int i = 0; i < 128; i++) {
			info->map[i] = i;
			info->map[i + 128] = cp1251[i];
		}
		return XML_STATUS_OK;
	} else if (strcasecmp(name, "windows-1252") == 0) {
		for (int i = 0; i < 128; i++) {
			info->map[i] = i;
			info->map[i + 128] = cp1252[i];
		}
		return XML_STATUS_OK;
	}
	return XML_STATUS_ERROR;
}

int ZLXMLReader::tag(const char *name) {
	const Tag *_tags = tags();
	for (int i = 0; ; i++) {
		if ((_tags[i].tagName == 0) || (strcmp(name, _tags[i].tagName) == 0)) {
			return _tags[i].tagCode;
		}
	}
}

static void parseDTD(XML_Parser parser, const std::string &fileName) {
	XML_Parser entityParser = XML_ExternalEntityParserCreate(parser, 0, 0);
	ZLInputStream *entityStream = ZLInputStream::createStream(fileName);
	if (entityStream->open()) {
		const size_t BUFSIZE = 2048;
		char buffer[BUFSIZE];
		size_t length;
		do {
			length = entityStream->read(buffer, BUFSIZE);
			if (XML_Parse(entityParser, buffer, length, 0) == XML_STATUS_ERROR) {
				break;
      }
    } while (length == BUFSIZE);
	}
	XML_ParserFree(entityParser);
	delete entityStream;
}

void ZLXMLReader::readDocument(ZLInputStream &stream) {
	if (!stream.open()) {
		return;
	}

	XML_Parser parser = XML_ParserCreate(NULL);
	XML_UseForeignDTD(parser, XML_TRUE);

	const std::vector<std::string> &dtds = externalDTDs();
	for (std::vector<std::string>::const_iterator it = dtds.begin(); it != dtds.end(); it++) {
		parseDTD(parser, *it);
	}

	XML_SetUserData(parser, this);
	XML_SetStartElementHandler(parser, fStartElementHandler);
	XML_SetEndElementHandler(parser, fEndElementHandler);
	XML_SetCharacterDataHandler(parser, fCharacterDataHandler);
  XML_SetUnknownEncodingHandler(parser, fUnknownEncodingHandler, NULL);

	const size_t BUFSIZE = 2048;
	char buffer[BUFSIZE];
	size_t length;
	do {
		length = stream.read(buffer, BUFSIZE);
		if (XML_Parse(parser, buffer, length, 0) == XML_STATUS_ERROR) {
			break;
    }
  } while ((length == BUFSIZE) && !myDoBreak);

	XML_ParserFree(parser);
	stream.close();
}

static std::vector<std::string> EMPTY_VECTOR;

const std::vector<std::string> &ZLXMLReader::externalDTDs() const {
	return EMPTY_VECTOR;
}
