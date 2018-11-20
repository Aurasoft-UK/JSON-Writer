#ifndef __JSON_WRITE_READER
#define __JSON_WRITE_READER

// Simple JSON Creator
// Author: Jayce Young
// Copyright (c) Aurasoft UK & Skyline Game Engine 2008-present day
// ------------------------------------------------------------------

#include "SkyString.h"
#include "SkyVector2.h"
#include "SkyVector3.h"
#include "SkyVector4.h"

/*
EXAMPLE USAGE:

	JSONWriter parser;

	// EXAMPLE 01:
	// =============================================================================

	// JSON reads a lot like blocks or containers and you can create a new container by:
	JSONWriter::Container* container1 = parser->addContainer("Properties", 1, false);

	// Then write properties to the container
	parser->write("root prop", "Value");
	container1->write("Prop", "Value");

	// Add a sub container that would appear tabbed into the last container.
	{
		JSONWriter::Container* container2 = parser->addContainer("SubProps", 1, true);
		container2->write("Prop", "\"Value\"");
		container2->write("Prop1", "1");
		container2->write("Prop1", "[0,0,0]");
		container2->write("Prop1", "[0,0]");
		container2->close();
	} container1->close(); // Always close your containers

	// Call generate to add the ending snippets and then write the file to a location on you disk
	SkySring filepath = "myfile.json";
	parser->generate(filepath);

	// EXAMPLE 02:
	// =============================================================================
	JSONWriter document;
	document.setIgnoreBlanks(true); // If a value is passed in and blank, then it is not needed and since it is json, it wont have a problem if the property is missing.
	document.write("Version",				version);
	document.write("GUIFileVersion",		GUIFileVersion);
	document.write("TriggerDefaultWarning",	triggerDefaultWarning);

	JSONWriter::Container* container = NULL;
	container = document.addContainer("Element Data", 1, true);

	for (int i = 0; i < elements.size(); i++){
		ElementData * data = elements[i];
		if (!data) continue;

		JSONWriter::Container* elemCont = document.addContainer("Element " + toString(i), 2, false);
			elemCont->write("Name",			data->Name);
			elemCont->write("Type",			data->Type);
			elemCont->write("ID",			data->ID);
			elemCont->write("Style",		data->Style);
			elemCont->write("Position",		data->Position);
			elemCont->write("Internal id",	data->element->GetId().CString());

			if (data->getParent()){
				elemCont->write("Parent Name", data->getParent()->Name);
			}else{
				elemCont->write("Parent Name", "");
			}

			JSONWriter::Container* childCont = document.addContainer("Children", 3, false);
			for (data->childIttr = data->getChildren().begin(); data->childIttr != data->getChildren().end(); data->childIttr++){
				childCont->write("Child_" + toString(counter) + "_Name", (*data->childIttr)->Name);
			}childCont->close();

			JSONWriter::Container* propsCont = document.addContainer("Properties", 3, false);
			for (data->propIttr = data->elemProps.begin(); data->propIttr != data->elemProps.end(); data->propIttr++){
				propsCont->write(data->propIttr->first, data->propIttr->second);
			}propsCont->close();

			JSONWriter::Container* attribsCont = document.addContainer("Attributes", 3, false);
			for (map_strittr = data->elementAttributes.begin(); map_strittr != data->elementAttributes.end(); map_strittr++){
				attribsCont->write(map_strittr->first, map_strittr->second);
			}attribsCont->close();

			JSONWriter::Container* customDataCont = document.addContainer("Custom Data", 3, false);
			customDataCont->write( "setElementText",  data->customData.setElementText	);
			customDataCont->write( "closeGUIOnClick", data->customData.closeGUIOnClick	);
			customDataCont->write("LoadGUIOnClick", data->customData.LoadGUIOnClick);
			{
				JSONWriter::Container* textValuesCont = document.addContainer("Text Values", 4, false);
				for (propIttr = data->customData.setTextValues.begin(); propIttr != data->customData.setTextValues.end(); propIttr++){
					textValuesCont->write(propIttr->first, propIttr->second);
				}textValuesCont->close();

				JSONWriter::Container* loadFileCont = document.addContainer("Load Filenames", 4, false);
				for (unsigned int f = 0; f < data->customData.loadFilenames.size(); f++){
					loadFileCont->write("loadfile" + toString(f), data->customData.loadFilenames[f]);
				}loadFileCont->close();

				JSONWriter::Container* closeFileCont = document.addContainer("Load Filenames", 4, false);
				for (unsigned int f = 0; f < data->customData.closeFilenames.size(); f++){
					closeFileCont->write("closefile" + toString(f), data->customData.closeFilenames[f]);
				}closeFileCont->close();

				JSONWriter::Container* customHooks = document.addContainer("Custom Hooks", 4, true); // True to signify last block in this chain
				for (unsigned int f = 0; f < VisualGUICustomEvent::DT_NUMEVENTS; f++){
					customHooks->write(data->customData.EnumToString[f], data->customData.getEventData[f]);
				}customHooks->close();


			} customDataCont->close();

			JSONWriter::Container* typeCont = document.addContainer("Type Properties", 3, true);
			if (data->Type == VisualElementTypeStr::Button){
				typeCont->write("normal_DivID", data->buttonData->normal_DivID);
				typeCont->write("hover_DivID", data->buttonData->hover_DivID);
				typeCont->write("pressed_DivID", data->buttonData->pressed_DivID);

				typeCont->write("image_Normal", data->buttonData->image_Normal);
				typeCont->write("image_Hover", data->buttonData->image_Hover);
				typeCont->write("image_Pressed", data->buttonData->image_Pressed);

				typeCont->write("image_N_Offset", data->buttonData->image_N_Offset);
				typeCont->write("image_H_Offset", data->buttonData->image_H_Offset);
				typeCont->write("image_P_Offset", data->buttonData->image_P_Offset);
				typeCont->write("image_N_Scale", data->buttonData->image_N_Scale);
				typeCont->write("image_H_Scale", data->buttonData->image_H_Scale);
				typeCont->write("image_P_Scale", data->buttonData->image_P_Scale);
			}else if (data->Type == VisualElementTypeStr::Checkbox){
				typeCont->write("checkboxInnerID", data->checkboxData->input_checkboxID);
			}typeCont->close();
		
		elemCont->close(); // Close this element block
	}

	// Close the last block
	container->close();

	// Now generate and write the file.
	document.generate(vDataFile);
*/
/*
class JSONWriteBase
{
public:
	JSONWriteBase(){}
	~JSONWriteBase(){}

	void write(SkyString prop, SkyString value)		{ write(prop.c_str(), ("\"" + value + "\"").c_str(), true); }
	void write(SkyString prop, const char* value)	{ write(prop.c_str(), ("\"" + SkyString(value) + "\"").c_str(), true); }
	void write(SkyString prop, float value)			{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, size_t value)		{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, int value)			{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, unsigned int value)	{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, bool value)			{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, SkyVector2 value)	{ write(prop.c_str(), ("[" + toString(value.x) + "," + toString(value.y) + "]").c_str(), true); }
	void write(SkyString prop, SkyVector3 value)	{ write(prop.c_str(), ("[" + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), true); }
	void write(SkyString prop, SkyVector4 value)	{ write(prop.c_str(), ("[" + toString(value.w) + "," + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), true); }
	void write(const char * prop, SkyString value)		{ write(prop, ("\"" + value + "\"").c_str(), false); }
	void write(const char * prop, const char* value)	{ write(prop, ("\"" + SkyString(value) + "\"").c_str(), false); }
	void write(const char * prop, float value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, size_t value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, int value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, unsigned int value)	{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, bool value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, SkyVector2 value)	{ write(prop, ("[" + toString(value.x) + "," + toString(value.y) + "]").c_str(), false); }
	void write(const char * prop, SkyVector3 value)	{ write(prop, ("[" + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), false); }
	void write(const char * prop, SkyVector4 value)	{ write(prop, ("[" + toString(value.w) + "," + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), false); }

	// Proper write - must be overwritten.
	virtual void write(const char* prop, const char* value, bool __unused__) = 0;
};*/

namespace JSONUtilities
{
	SkyVector2 parseVector2Array(const rapidjson::Value &jsonArray)
	{
		SkyVector2 retVal = SkyVector2(0, 0);

		const rapidjson::SizeType arraySize = std::min(2u, jsonArray.Size());
		for (rapidjson::SizeType i = 0; i < arraySize; ++i){
			if (jsonArray[i].IsInt()){
				retVal[i] = jsonArray[i].GetInt();
			}else if (jsonArray[i].IsDouble()){
				retVal[i] = static_cast<float>(jsonArray[i].GetDouble());
			}
		}

		return retVal;
	}

	SkyVector3 parseVector3Array(const rapidjson::Value &jsonArray)
	{
		SkyVector3 retVal = SkyVector3(0, 0, 0);

		const rapidjson::SizeType arraySize = std::min(3u, jsonArray.Size());
		for (rapidjson::SizeType i = 0; i < arraySize; ++i){
			if (jsonArray[i].IsInt()){
				retVal[i] = jsonArray[i].GetInt();
			}else if (jsonArray[i].IsDouble()){
				retVal[i] = static_cast<float>(jsonArray[i].GetDouble());
			}
		}

		return retVal;
	}

	SkyVector4 parseVector4Array(const rapidjson::Value &jsonArray)
	{
		SkyVector4 retVal = SkyVector4(0, 0, 0, 0);

		const rapidjson::SizeType arraySize = std::min(3u, jsonArray.Size());
		for (rapidjson::SizeType i = 0; i < arraySize; ++i){
			if (jsonArray[i].IsInt()){
				retVal[i] = jsonArray[i].GetInt();
			}else if (jsonArray[i].IsDouble()){
				retVal[i] = static_cast<float>(jsonArray[i].GetDouble());
			}
		}

		return retVal;
	}
};

class JSONWriter /*: public JSONWriteBase*/
{
public:
	enum WrittenType { WT_NONE, WT_ROOTPARAM, WT_PARAM, WT_CONTAINER, WT_CLOSE };

	JSONWriter(){
		rootPropWritten = false;
		JSONfile = "{\n";
		lastContainer = NULL;
		ignoreBlanks = false;
		lastWrittenType = WT_NONE;
	}
	~JSONWriter(){}

	void setIgnoreBlanks(bool state){ ignoreBlanks = state; }
	bool getIgnoreBlanks(){ return ignoreBlanks; }
	
	class Container /*: public JSONWriteBase*/
	{
	public:
		enum TAB_SECTION{ str_start, str_end };
	
		Container(SkyString name, int depth, SkyString &_filestr/*, bool _lastBlock*/)
		{
			tabDepth=depth;
			fileStr = &_filestr;
			//lastBlock = _lastBlock;
			firstProp = true;
			_name = name;
			
			int tabDepthI = tabDepth<=0?0:tabDepth + 1;
			_tabStringHeader = getTabs(tabDepth);
			_tabString = getTabs(tabDepthI);

			*fileStr += _tabStringHeader + "\"" + _name + "\" : \n" + _tabStringHeader + "{\n";
		}
		~Container(){}

		JSONWriter* getParent(){
			return _parent;
		}

		void setParent(JSONWriter& parent){
			_parent = &parent;
		}
		
		SkyString getTabs(int &depth){
			SkyString tabText = "";
			for(unsigned int i=0;i<depth;i++){
				tabText+="\t";
			}
			return tabText;
		}
		
		// Write helpers
		void write(SkyString prop, SkyString value)		{ write(prop.c_str(), ("\"" + value + "\"").c_str(), true); }
		void write(SkyString prop, const char* value)	{ write(prop.c_str(), ("\"" + SkyString(value) + "\"").c_str(), true); }
		void write(SkyString prop, float value)			{ write(prop.c_str(), toString(value).c_str(), true); }
		void write(SkyString prop, size_t value)		{ write(prop.c_str(), toString(value).c_str(), true); }
		void write(SkyString prop, int value)			{ write(prop.c_str(), toString(value).c_str(), true); }
		void write(SkyString prop, unsigned int value)	{ write(prop.c_str(), toString(value).c_str(), true); }
		void write(SkyString prop, bool value)			{ write(prop.c_str(), toString(value).c_str(), true); }
		void write(SkyString prop, SkyVector2 value)	{ write(prop.c_str(), ("[" + toString(value.x) + "," + toString(value.y) + "]").c_str(), true); }
		void write(SkyString prop, SkyVector3 value)	{ write(prop.c_str(), ("[" + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), true); }
		void write(SkyString prop, SkyVector4 value)	{ write(prop.c_str(), ("[" + toString(value.w) + "," + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), true); }
		void write(const char * prop, SkyString value)		{ write(prop, ("\"" + value + "\"").c_str(), false); }
		void write(const char * prop, const char* value)	{ write(prop, ("\"" + SkyString(value) + "\"").c_str(), false); }
		void write(const char * prop, float value)			{ write(prop, toString(value).c_str(), false); }
		void write(const char * prop, size_t value)			{ write(prop, toString(value).c_str(), false); }
		void write(const char * prop, int value)			{ write(prop, toString(value).c_str(), false); }
		void write(const char * prop, unsigned int value)	{ write(prop, toString(value).c_str(), false); }
		void write(const char * prop, bool value)			{ write(prop, toString(value).c_str(), false); }
		void write(const char * prop, SkyVector2 value)	{ write(prop, ("[" + toString(value.x) + "," + toString(value.y) + "]").c_str(), false); }
		void write(const char * prop, SkyVector3 value)	{ write(prop, ("[" + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), false); }
		void write(const char * prop, SkyVector4 value)	{ write(prop, ("[" + toString(value.w) + "," + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), false); }
		
		// Proper write  
		void write(const char* prop, const char* value, bool __unused__){
			SkyString sValue = value;
			if (getParent()->getIgnoreBlanks() && sValue == "" || getParent()->getIgnoreBlanks() && sValue == "\"\""){
				return;
			}

			if (!firstProp){ *fileStr += ",\n"; }

			*fileStr += _tabString + "\"" + prop + "\" : " + value;
			firstProp = false;
			_parent->lastWrittenType = WrittenType::WT_PARAM;
		}
		
		void close(){
			*fileStr += "\n" + _tabStringHeader + "}";
			_parent->lastWrittenType = WrittenType::WT_CLOSE;
		}
			
	private:
		bool firstProp;
		SkyStringMap_S dataProps;
		int tabDepth;
		//bool lastBlock;
		SkyString _tabString;
		SkyString _tabStringHeader;
		SkyString *fileStr;
		SkyString _name;
		JSONWriter *_parent;
	};
	
	void generate(SkyString filename)
	{
		JSONfile += "\n}\n";
		
		std::ofstream outFile;
		outFile.open(filename, std::ofstream::out | std::ofstream::trunc);
		outFile << JSONfile;
		outFile.close();
		
		for(ittr = containers.begin(); ittr != containers.end(); ittr++){
			Container* container = (*ittr);
			SAFE_DELETE(container);
		}
		
		containers.clear();
	}

	Container* addContainer(SkyString name, int depth){
		if (lastWrittenType == WrittenType::WT_ROOTPARAM ||
			lastWrittenType == WrittenType::WT_PARAM ||
			lastWrittenType == WrittenType::WT_CLOSE){
			JSONfile += ",\n"; 
		}

		Container* newContainer = new Container(name, depth, JSONfile);
		newContainer->setParent(*this);
		containers.push_back(newContainer);
		lastContainer = newContainer;
		lastWrittenType = WrittenType::WT_CONTAINER;
		return newContainer;
	}
	
	// Write on the root of the file and not in a container.
	void write(SkyString prop, SkyString value)		{ write(prop.c_str(), ("\"" + value + "\"").c_str(), true); }
	void write(SkyString prop, const char* value)	{ write(prop.c_str(), ("\"" + SkyString(value) + "\"").c_str(), true); }
	void write(SkyString prop, float value)			{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, size_t value)		{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, int value)			{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, unsigned int value)	{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, bool value)			{ write(prop.c_str(), toString(value).c_str(), true); }
	void write(SkyString prop, SkyVector2 value)	{ write(prop.c_str(), ("[" + toString(value.x) + "," + toString(value.y) + "]").c_str(), true); }
	void write(SkyString prop, SkyVector3 value)	{ write(prop.c_str(), ("[" + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), true); }
	void write(SkyString prop, SkyVector4 value)	{ write(prop.c_str(), ("[" + toString(value.w) + "," + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), true); }
	void write(const char * prop, SkyString value)		{ write(prop, ("\"" + value + "\"").c_str(), false); }
	void write(const char * prop, const char* value)	{ write(prop, ("\"" + SkyString(value) + "\"").c_str(), false); }
	void write(const char * prop, float value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, size_t value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, int value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, unsigned int value)	{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, bool value)			{ write(prop, toString(value).c_str(), false); }
	void write(const char * prop, SkyVector2 value)	{ write(prop, ("[" + toString(value.x) + "," + toString(value.y) + "]").c_str(), false); }
	void write(const char * prop, SkyVector3 value)	{ write(prop, ("[" + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), false); }
	void write(const char * prop, SkyVector4 value)	{ write(prop, ("[" + toString(value.w) + "," + toString(value.x) + "," + toString(value.y) + "," + toString(value.z) + "]").c_str(), false); }
	
	void write(const char* prop, const char* value, bool unused)
	{
		if (lastContainer){ lprint("[JSON Writer] Cannot write to the root as a container is currently active."); return; }

		SkyString sValue = value;
		if (getIgnoreBlanks() && sValue == "" || getIgnoreBlanks() && sValue == "\"\""){
			return;
		}

		if (rootPropWritten){ JSONfile += ",\n"; }
		JSONfile += "\t\"" + SkyString(prop) + "\" : " + SkyString(value);
		rootPropWritten = true;
		lastWrittenType = WrittenType::WT_ROOTPARAM;
	}
	
private:
	WrittenType lastWrittenType;
	SkyString JSONfile; 
	Container*lastContainer;
	std::vector<Container*> containers;
	std::vector<Container*>::iterator ittr;
	bool rootPropWritten;
	bool ignoreBlanks;
};



#endif
