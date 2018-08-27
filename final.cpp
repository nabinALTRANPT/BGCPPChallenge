
#include <iostream>     //Header files 
#include <string>
#include "tinyxml.h"
#include <stdio.h>
#include <fstream>
#include <jsoncpp/json/json.h>
#include<jsoncpp/json/writer.h>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>

using namespace std;

XERCES_CPP_NAMESPACE_USE


struct jdummy {              // Dummy data
	string filename;
	string stringMember;
	string intmember;
};

struct dummy {
	string filename;
	string stringMember;
	string intmember;
};

class ParserErrorHandler : public ErrorHandler              // Error Handler for XML validation 
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


class file {                        // Creation of XMl files using tinyxml lib

public:

	void xml(dummy *d) {

		

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


int main() {


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

	d[0].filename = "data1.xml";
	d[0].stringMember = "str1";
	d[0].intmember = "1";

	d[1].filename = "data2.xml";
	d[1].stringMember = "str2";
	d[1].intmember = "2";

	d[2].filename = "data3.xml";
	d[2].stringMember = "str3";
	d[2].intmember = "3";

	int myChoice = 0;

	std::cout << "********** Main Menu **********" << std::endl;               // Console menu
	std::cout << "(1): To create XML files and validate enter 1" << std::endl;
	std::cout << "(2): To Export data to JSON files presss 2" << std::endl;
	std::cout << "(3): To quit the program enter 3 " << std::endl;
	std::cin >> myChoice;

	switch (myChoice)
	{
	case 1:

		for (int index = 0; index < 3; index++) {          // case 1 = XML FILE CREATION ADN VALIDATION !
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
			
			const char *xmlfile[50] = {"data1.xml","data2.xml","data3.xml" };
			domParser.parse(xmlfile[index]);
			if (domParser.getErrorCount() == 0)
				printf("XML file validated against the schema successfully\n");
			else
				printf("XML file doesn't conform to the schema\n");

			
		}
		cout << "Three XML files are created and validated, Thank you\n";

		XMLPlatformUtils::Terminate();
			main();
		break;

	case 2:

		for (int i = 0; i < 3; i++) {                // case 2 =  EXPORTED TO JSON FILE !

			std::ofstream file_id;
			file_id.open(j[i].filename);

			Json::Value event;

			event["stringMember"] = j[i].stringMember;
			event["intMember"] = j[i].intmember;
			file_id << event << std::endl;
			file_id.close();
			std::cout << (j[i].filename) << std::endl;
			std::cout << event << std::endl;
		}
		std::cout << "XML data has been exported to JSON files successfully , Thank you" << std::endl;
			main();
		break;

	

	case 3:   
			printf("Thank you\n");                    // QUIT PROGRAM 
			return 0;

	default:
		std::cout << "ERROR! You have selected an invalid choice." << std::endl;
		break;
	
	}
	getchar();
	return 0;
}
