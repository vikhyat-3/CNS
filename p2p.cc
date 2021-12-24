#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;
int main(int argc,char* argv[]){
    std::string socketType= "ns3::TcpSocketFactory";
    CommandLine cmd;
    cmd.Parse(argc,argv);
    NodeContainer nodes;
    nodes.Create(3);

    InternetStackHelper stack;
    stack.Install(nodes);

    PointToPointHelper p2p1;
    p2p1.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
    p2p1.SetChannelAttribute("Delay",StringValue("1ms"));
    NetDeviceContainer devices;
    devices=p2p1.Install(nodes.Get(0),nodes.Get(1));
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0","255.255.255.0");
    Ipv4InterfaceContainer interfaces= address.Assign(devices);

    Ptr<RateErrorModel> em=CreateObject<RateErrorModel> ();
    em->SetAttribute("ErrorRate",DoubleValue(0.0001));
    devices.Get(1)->SetAttribute("ReceiveErrorModel",PointerValue(em));
    devices=p2p1.Install(nodes.Get(1),nodes.Get(2));
    interfaces=address.Assign(devices);

    uint16_t port=7;
    uint32_t payloadsize=1448;

    OnOffHelper onOff(socketType,Ipv4Address::GetAny());
    onOff.SetAttribute("OnTime",StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    onOff.SetAttribute("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    onOff.SetAttribute("PacketSize",UintegerValue(payloadsize));
    onOff.SetAttribute("DataRate",StringValue("50Mbps"));

    
    Address localAdd(InetSocketAddress(Ipv4Address::GetAny()));
    PacketSinkHelper psh(socketType,localAdd);
    
    ApplicationContainer sinkApps=psh.Install(nodes.Get(2));
    sinkApps.Start(Seconds(0.));
    sinkApps.Stop(Seconds(20.));
    
    AddressValue remoteAdd(InetSocketAddress(interfaces.GetAddress(1),port));
    onOff.SetAttribute("Remote",remoteAdd);
    ApplicationContainer apps=onOff.Install(nodes.Get(0));
    apps.Start(Seconds(1.));
    apps.Stop(Seconds(20.));
    
    
    AsciiTraceHelper ascii;
    p2p1.EnableAsciiAll(ascii.CreateFileStream("point2point.tr"));

    Simulator::Stop(Seconds(20.));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}