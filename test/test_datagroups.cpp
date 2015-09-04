#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include <mot.h>
#include <contenttypes.h>

#include "catch.hpp"
#include "../src/datagroups.h"

using namespace std;
using namespace mot;
using namespace msc;

TEST_CASE( "MSC datagroup encoding tests", "[msc]" ) {

	SECTION ("DATAGROUP") {
		string data("=====");
		vector<unsigned char> bytes;
		copy(data.begin(), data.end(), back_inserter(bytes));
		SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8541);
		int transportId = id->next();
		MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
		o.addParameter(new MimeType("application/txt"));
		SegmentEncoder encoder;
		vector<Segment*> segments = encoder.encode(o);
        cout << "encoded into " << segments.size() << " segments" << endl;
        DatagroupEncoder datagroupEncoder;
        vector<Datagroup*> datagroups = datagroupEncoder.encode_datagroups(segments);
        cout << "encoded into " << datagroups.size() << " datagroups" << endl;
		for(Datagroup* datagroup : datagroups)
		{
            cout << "datagroup" << endl;
            cout << "=========" << endl;
			cout << datagroup->encode();
            cout << endl;
		}
	}

}
