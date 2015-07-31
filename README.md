libmsc
======

Encoder/Decoder for MSC Datagroup and Packet data as per ETSI 300 401 Section 5.3, Main Service Channel (MSC).

# Current Status

# Examples

Encoding a simple text MOT object into Datagroups and write out the resultant data to the console.

```cpp
#include <vector>
#include <iostream>

#include "mot.h"
#include "datagroups.h"

using namespace mot;
using namespace std;

int main() {
    string data("=====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));
    SequentialTransportIdGenerator::initial = 8541;
    SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance();
    int transportId = id->next();
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.addParameter(new MimeType("application/txt"));
    SegmentEncoder encoder;
    vector<Segment*> segments = encoder.encode(o);
    int i = 0;
    SegmentDatagroupType last_type;
    for(Segment* segment : segments)
    {
        if(last_type && last_type != segment->getType()) i = 0;
        Datagroup d(*segment, i%16);
        cout << d.encode();
    }
    return  0;
}
```
