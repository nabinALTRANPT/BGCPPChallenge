#include <stdio.h>
#include<iostream>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <string>
#include "tinyxml.h"
#include <fstream>
#include <jsoncpp/json/json.h>
#include<jsoncpp/json/writer.h>

using namespace std;
using namespace xercesc;

XERCES_CPP_NAMESPACE_USE


struct jdummy {
	string filename;
	string stringMember;
	string intmember;
};

struct dummy {
	string filename;
	string stringMember;
	string intmember;
};


class ParserErrorHandler : public ErrorHandler
{
private:
	void reportParseException(const SAXParseException& ex)
	{
		char* msg = XMLString::transcode(ex.getMessage());
		fprintf(stderr, "at line %llu column %llu, %s\n",
			ex.getColumnNumber(), ex.getLineNumber(), msg);
		XMLString::release(&msg);
	}

public:
	void warning(const SAXParseException& ex)
	{
		reportParseException(ex);
	}

	void error(const SAXParseException& ex)
	{
		reportParseException(ex);
	}

	void fatalError(const SAXParseException& ex)
	{
		reportParseException(ex);
	}

	void resetErrors()
	{
	
	}
};


class file {

public:

	void xml(dummy *d) {

		//cout << "My args " << d->filename << " " << d->stringMember << " " << d->intmember << "\n";

		TiXmlDocument doc = TiXmlDocument();

		TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(decl);

		TiXmlElement* element = new TiXmlElement("bit:a");
		element->SetAttribute("xmlns:bit", "http://example.org/types");
		doc.LinkEndChild(element);

		TiXmlElement* element2 = new TiXmlElement("stringMember");
		element->LinkEndChild(element2);
		TiXmlText* text2 = new  TiXmlText(d->stringMember.c_str());
		element2->LinkEndChild(text2);

		TiXmlElement* element1 = new TiXmlElement("intMember");
		element->LinkEndChild(element1);
		TiXmlText* text1 = new TiXmlText(d->intmember.c_str());
		element1->LinkEndChild(text1);

		doc.SaveFile(d->filename.c_str());



	}
};


void main() {

	file x;

	jdummy j[3];

	j[0].filename = "data1.json";
	j[0].stringMember = "str1";
	j[0].intmember = "1";

	j[1].filename = "data2.json";
	j[1].stringMember = "str2";
	j[1].intmember = "2";

	j[2].filename = "data3.json";
	j[2].stringMember = "str3";
	j[2].intmember = "3";

	dummy d[3];

	d[0].filename = "mata1.xml";
	d[0].stringMember = "str1";
	d[0].intmember = "1";

	d[1].filename = "mata2.xml";
	d[1].stringMember = "str2";
	d[1].intmember = "2";

	d[2].filename = "mata3.xml";
	d[2].stringMember = "str3";
	d[2].intmember = "3";

	int myChoice = 0;

	std::cout << "********** Main Menu **********" << std::endl;
	std::cout << "(1): To create XML files enter 1" << std::endl;
	std::cout << "(2): To Export data to JSON files presss 2" << std::endl;
	std::cout << "(3): To vaidate press XML files against XSD press 3 " << std::endl;
	std::cin >> myChoice;

	switch (myChoice)
	{
	case 1:

		for (int index = 0; index < 3; index++) {
			x.xml(&d[index]);

			XMLPlatformUtils::Initialize();
			XercesDOMParser domParser;

			if (domParser.loadGrammar("d.xsd", Grammar::SchemaGrammarType) == NULL)
			{
				fprintf(stderr, "couldn't load schema\n");

			}

			ParserErrorHandler parserErrorHandler;

			domParser.setErrorHandler(&parserErrorHandler);
			domParser.setValidationScheme(XercesDOMParser::Val_Auto);
			domParser.setDoNamespaces(true);
			domParser.setDoSchema(true);
			domParser.setValidationConstraintFatal(true);

			domParser.parse("mata1.xml");
			if (domParser.getErrorCount() == 0)
				printf("XML file validated against the schema successfully\n");
			else
				printf("XML file doesn't conform to the schema\n");


		}
		cout << "Three XML files are created , Thank you\n";

		XMLPlatformUtils::Terminate();
		break;

	case 2:

		for (int i = 0; i < 3; i++) {

			std::ofstream file_id;
			file_id.open(j[i].filename);

			Json::Value event;

			event["stringMember"] = j[i].stringMember;
			event["intMember"] = j[i].intmember;
			file_id.close();
			std::cout << (j[i].filename) << std::endl;
			std::cout << event << std::endl;
		}
		std::cout << "XML data has been exported to JSON files successfully , Thank you" << std::endl;
		break;



	case 3:
		printf("SchemaValidator must take  <schema file> <xml file> as argument\n");
		return 0;

	default:
		std::cout << "ERROR! You have selected an invalid choice." << std::endl;
		break;

	}
	getchar();
	return 0;


}










