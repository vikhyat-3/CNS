#include"ns3/core-module.h"
#include"ns3/network-module.h"
#include"ns3/internet-module.h"
#include"ns3/csma-module.h"
#include"ns3/applications-module.h" 
#include"ns3/internet-apps-module.h"
using namespace ns3;

static void PingRtt(std::string context, Time rtt){
	std::cout<<context<<" "<<rtt<<std::endl;
}

int main(int argc,char *argv[])
{
        CommandLine cmd;
        cmd.Parse(argc,argv);
        NodeContainer nodes;
        nodes.Create(6);
        
        InternetStackHelper stack;
        stack.Install (nodes);
        
        CsmaHelper csma;
        csma.SetChannelAttribute("DataRate",DataRateValue(DataRate("5Mbps")));
        csma.SetChannelAttribute("Delay",TimeValue(MilliSeconds(0.2)));
        
        NetDeviceContainer devices;
        devices=csma.Install(nodes);
        
        Ipv4AddressHelper address;
        address.SetBase("192.168.1.0","255.255.255.0");
        Ipv4InterfaceContainer interfaces= address.Assign(devices);
        
        uint16_t port=9;
        OnOffHelper onoff("ns3::UdpSocketFactory",Address(InetSocketAddress(interfaces.GetAddress(2),port)));
        onoff.SetConstantRate(DataRate("5Mb/s"));
        
        ApplicationContainer app= onoff.Install(nodes.Get(0));
        app.Start(Seconds(6.0));
        app.Start(Seconds(10.0));
        
        PacketSinkHelper sink("ns3::UdpSocketFactory",Address(InetSocketAddress(Ipv4Address::GetAny(),port)));
        app= sink.Install(nodes.Get(2));
        app.Start(Seconds(0.0));
        
        V4PingHelper ping=V4PingHelper(interfaces.GetAddress(2));
        NodeContainer pinger;
        pinger.Add(nodes.Get(0));
        pinger.Add(nodes.Get(1));
        
        ApplicationContainer apps= ping.Install(pinger);
        apps.Start(Seconds(2.0));
        apps.Stop(Seconds(5.0));
        
        Config::Connect("/NodeList/*/ApplicationList/*/$ns3::V4Ping/Rtt",MakeCallback(&PingRtt));
        
        AsciiTraceHelper ascii;
        csma.EnableAsciiAll(ascii.CreateFileStream("ping1.tr"));
        Simulator::Run();
        Simulator:: Destroy();
        
}
