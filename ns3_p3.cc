#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-application-helper.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE("prg3");

int main(int argc , char * argv[])
{
    CommandLine cmd;
    cmd.Parse(argc,argv);
    
    NodeContainer nodes;
    nodes.Create(4);
    
    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("5Mbps"));
    csma.SetChannelAttribute("Delay",TimeValue(MilliSeconds(0.0001)));
    
    NetDeviceContainer devices;
    devices = csma.Install(nodes);
    
    Ptr<RateErrorModel> em=CreateObject<RateErrorModel>();
    em->SetAttribute("ErrorRate" , DoubleValue(0.00001));
    devices.Get(1)->SetAttribute("ReceiveErrorModel" , PointerValue(em));
    
    InternetStackHelper stack;
    stack.Install(nodes);
    
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0" , "255.255.255.0");
    Ipv4InterfaceContainer interfaces=address.Assign(devices);
    
    uint16_t sinkPort=8080;
    
    Address sinkAddress(InetSocketAddress(interfaces.GetAddress(1),sinkPort));
    PacketSinkHelper packetSinkHelper("ns3::TcpSocketFactory" , InetSocketAddress(Ipv4Address::GetAny(),sinkPort));
    
    ApplicationContainer sinkApps=packetSinkHelper.Install(nodes.Get(1));
    sinkApps.Start(Seconds(0.));
    sinkApps.Stop(Seconds(20.));
    
    Ptr<Socket> ns3TcpSocket=Socket::CreateSocket(nodes.Get(0),TcpSocketFactory::GetTypeId());
    ns3TcpSocket->TraceConnectWithoutContext("CongestionWindow" , MakeCallback(&CwndChange));
    
    Ptr<NetworkApplication> app=CreateObject<NetworkApplication>();
    app->Setup(ns3TcpSocket,sinkAddress,1040,1000,DataRate("50Mbps"));
    nodes.Get(0)->AddApplication(app);
    app->SetStartTime(Seconds(1.));
    app->SetStopTime(Seconds(20.));
    
    devices.Get(1)->TraceConnectWithoutContext("PhyRxDrop" , MakeCallback(&RxDrop));
    
    AsciiTraceHelper ascii;
    csma.EnableAsciiAll(ascii.CreateFileStream("ns3l3_180.tar"));
    csma.EnablePcapAll(std::string("ns3l3_180.tar"),true);

    Simulator::Stop(Seconds(20.));
    Simulator::Run();
    Simulator::Destroy();
    
}


