#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/lte-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/config-store-module.h"
#include "ns3/netanim-module.h"
#include "ns3/gnuplot.h"
#include <math.h>
#include <random>
#include<map>
#include<string>
using namespace ns3;
using namespace  std;

int seed=46;
map<Ipv4Address, uint32_t> ueToEnbMap;
map<u_int32_t,vector<double>> enbStats;
map<Ipv4Address, uint32_t> NrDevice;
map<Ipv4Address,double> ResourceFactor;

void ThroughputMonitor (FlowMonitorHelper *fmhelper, Ptr<FlowMonitor> flowMon)
{
double localThrou=0;
std::map<FlowId, FlowMonitor::FlowStats> flowStats = flowMon->GetFlowStats();
Ptr<Ipv4FlowClassifier> classing = DynamicCast<Ipv4FlowClassifier> (fmhelper->GetClassifier());
for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator stats = flowStats.begin (); stats != flowStats.end (); ++stats)
{
Ipv4FlowClassifier::FiveTuple fiveTuple = classing->FindFlow (stats->first);
// std::cout<<stats->first<<"  "<<fiveTuple.sourceAddress<<"-------->"<<fiveTuple.destinationAddress<<std::endl;

if (fiveTuple.sourceAddress == Ipv4Address("1.0.0.2") /*|| fiveTuple.sourceAddress == Ipv4Address("7.0.0.2") || fiveTuple.sourceAddress == Ipv4Address("7.0.0.3")*/)
{
// std::cout<<stats->first<<"  "<<fiveTuple.sourceAddress<<"-------->"<<fiveTuple.destinationAddress<<std::endl;
// std::cout<<ueToEnbMap[fiveTuple.destinationAddress]<<std::endl;
// std::cout<<"Flow ID     : " << stats->first <<" ; "<< fiveTuple.sourceAddress <<" -----> "<<fiveTuple.destinationAddress<<std::endl;
// std::cout<<"Tx Packets : " << stats->second.txPackets<<std::endl;
// std::cout<<"Rx Packets : " << stats->second.rxPackets<<std::endl;
// std::cout<<"Duration    : "<<(stats->second.timeLastRxPacket.GetSeconds()-stats->second.timeFirstTxPacket.GetSeconds())<<std::endl;
// std::cout<<"Last Received Packet  : "<< stats->second.timeLastRxPacket.GetSeconds()<<" Seconds"<<std::endl;
//  std::cout<<"Throughput: " << stats->second.rxBytes * 8.0 / (stats->second.timeLastRxPacket.GetSeconds()-stats->second.timeFirstTxPacket.GetSeconds())/1024  << " Kbps"<<std::endl;
// std::cout<< "Mean{Delay}: " << (stats->second.delaySum.GetSeconds()/stats->second.rxPackets) << "\n";
// std::cout<< "Mean{Jitter}: " << (stats->second.jitterSum.GetSeconds()/(stats->second.rxPackets)) << "\n";
// std::cout<< "Total{Delay}: " << (stats->second.delaySum.GetSeconds()) << "\n";
// std::cout<< "Total{Jitter}: " << (stats->second.jitterSum.GetSeconds()) << "\n";
// std::cout<< "Lost Packets: " << (stats->second.lostPackets) << "\n";
// std::cout<< "Dropped Packets: " << (stats->second.packetsDropped.size()) << "\n";
// localThrou=(stats->second.rxBytes * 8.0 / (stats->second.timeLastRxPacket.GetSeconds()-stats->second.timeFirstTxPacket.GetSeconds())/1024);
enbStats[ueToEnbMap[fiveTuple.destinationAddress]][0]+=(stats->second.rxBytes * 8.0 / (stats->second.timeLastRxPacket.GetSeconds()-stats->second.timeFirstTxPacket.GetSeconds())/1024);
enbStats[ueToEnbMap[fiveTuple.destinationAddress]][1]=max(stats->second.delaySum.GetSeconds()/stats->second.rxPackets,enbStats[ueToEnbMap[fiveTuple.destinationAddress]][1]);
enbStats[ueToEnbMap[fiveTuple.destinationAddress]][2]=max(stats->second.jitterSum.GetSeconds()/(stats->second.rxPackets),enbStats[ueToEnbMap[fiveTuple.destinationAddress]][2]);
enbStats[ueToEnbMap[fiveTuple.destinationAddress]][3]+=(stats->second.lostPackets);
enbStats[ueToEnbMap[fiveTuple.destinationAddress]][4]+=(1);
enbStats[ueToEnbMap[fiveTuple.destinationAddress]][5]+=NrDevice[fiveTuple.destinationAddress];
enbStats[ueToEnbMap[fiveTuple.destinationAddress]][6]+=ResourceFactor[fiveTuple.destinationAddress];

// updata gnuplot data
// DataSet.Add((double)Simulator::Now().GetSeconds(),(double) localThrou);
//  std::cout<<"---------------------------------------------------------------------------"<<std::endl;
}
}
for (auto &x : enbStats){
cout<<"EnB Number"<<x.first<<endl;
cout<<"Throughput=="<<x.second[0]/x.second[4]<<endl;
cout<<"Delay=="<<x.second[1]<<endl;
cout<<"Jitter=="<<x.second[2]<<endl;
cout<<"Packet Loss=="<<x.second[3]<<endl;
cout<<"Connected UE=="<<x.second[4]<<endl;
cout<<"5G UE=="<<x.second[5]<<endl;
cout<<"ResourceFactor=="<<x.second[6]/x.second[4]<<endl;
std::cout<<"---------------------------------------------------------------------------"<<std::endl;      
x.second={0,0,0,0,0,0,0};
}
cout<<"\n\n";

Simulator::Schedule(Seconds(1.0  ),&ThroughputMonitor, fmhelper, flowMon);
//if(flowToXml)
{
// flowMon->SerializeToXmlFile ("ThroughputMonitor.xml", true, true);
}

}


  std::vector<std::pair<int, int>> generate_users(int num_of_users, int area) {
  std::vector<std::pair<int, int>> users;
  // std::random_device rd;
  // std::mt19937 gen(rd());
  std::mt19937 gen(seed);
  std::uniform_real_distribution<> dis(0, area);

  for (int i = 0; i < num_of_users; ++i) {
  int x = round(dis(gen));
  int y = round(dis(gen));
  std::pair<int, int> user(x, y);
  users.push_back(user);
  }

  return users;
  }

  std::vector<std::pair<int, int>> generate_points(int num_points, int area, int min_distance) {
  std::vector<std::pair<int, int>> points;
  // std::random_device rd;
  // std::mt19937 gen(rd());
  std::mt19937 gen(seed);
  std::uniform_real_distribution<> dis(0, area);

  while (points.size() < num_points) {
  int x = round(dis(gen));
  int y = round(dis(gen));
  std::pair<int, int> point(x, y);

  bool valid = true;
  for (const auto& existing_point : points) {
  double distance = sqrt(pow(point.first - existing_point.first, 2) +
                        pow(point.second - existing_point.second, 2));
  if (distance < min_distance) {
    valid = false;
    break;
  }
  }

  if (valid) {
  points.push_back(point);
  }
  }
  return points;
  }




int main (int argc, char *argv[])
{


uint16_t numberOfUes = 1000;
uint16_t numberOfEnbs = 22;
//uint16_t numBearersPerUe = 2;
double simTime = 5.0;
//double distance = 100.0;

Config::SetDefault ("ns3::UdpClient::Interval", TimeValue (MilliSeconds (100)));
Config::SetDefault ("ns3::UdpClient::MaxPackets", UintegerValue (1000000));
Config::SetDefault ("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue(320));
Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));

// Command line arguments
CommandLine cmd;
cmd.AddValue ("numberOfUes", "Number of UEs", numberOfUes);
cmd.AddValue ("numberOfEnbs", "Number of eNodeBs", numberOfEnbs);
cmd.AddValue ("simTime", "Total duration of the simulation (in seconds)", simTime);
cmd.Parse (argc, argv);


Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
lteHelper->SetEpcHelper (epcHelper);


Ptr<Node> pgw = epcHelper->GetPgwNode ();
lteHelper->SetEnbDeviceAttribute ("UlBandwidth", UintegerValue (100));
lteHelper->SetEnbDeviceAttribute ("DlBandwidth", UintegerValue (100));

NodeContainer remoteHostContainer;
remoteHostContainer.Create (1);
Ptr<Node> remoteHost = remoteHostContainer.Get (0);
InternetStackHelper internet;
internet.Install (remoteHostContainer);


PointToPointHelper p2ph;
p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.00)));
NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
Ipv4AddressHelper ipv4h;
ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);


// Routing of the Internet Host (towards the LTE network)
Ipv4StaticRoutingHelper ipv4RoutingHelper;
Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
// interface 0 is localhost, 1 is the p2p device
remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);


NodeContainer ueNodes;
NodeContainer enbNodes;
enbNodes.Create (numberOfEnbs);
ueNodes.Create (numberOfUes);

auto users=generate_users(numberOfUes,4000);
auto bts=generate_points(numberOfEnbs,4000,200);

//Install Mobility Model
//Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
// for (uint16_t i = 0; i < numberOfEnbs; i++)
//   {
//     positionAlloc->Add (Vector (distance * 2 * i - distance, 0, 0));
//   }
// for (uint16_t i = 0; i < numberOfUes; i++)
//   {
//     positionAlloc->Add (Vector (0, 0, 0));
//   }
MobilityHelper mobility;
mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
mobility.Install (ueNodes);
mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
mobility.Install (enbNodes);

for (int i=0;i<users.size();i++){
Ptr<MobilityModel> uemobility = ueNodes.Get(i)->GetObject<MobilityModel>();
uemobility->SetPosition(Vector(users[i].first, users[i].second, 1.5));
}
for (int i=0;i<bts.size();i++){
Ptr<MobilityModel> enbmobility = enbNodes.Get(i)->GetObject<MobilityModel>();
enbmobility->SetPosition(Vector(bts[i].first,bts[i].second, 45));
}
// Install LTE Devices in eNB and UEs
NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

// Install the IP stack on the UEs
internet.Install (ueNodes);
Ipv4InterfaceContainer ueIpIfaces;
ueIpIfaces = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));

// internet.Install(enbNodes);
// Ipv4InterfaceContainer enbIfaces;
// enbIfaces =epcHelper->AssignUeIpv4Address(NetDeviceContainer(enbLteDevs));

// for (uint32_t i = 0; i < ueIpIfaces.GetN(); ++i) {
//     std::cout << "ue " << i << ": " << ueIpIfaces.GetAddress(i) << std::endl;
// }

// Attach all UEs to the first eNodeB
// for (uint16_t i = 0; i < numberOfUes; i++)
//   {
//     lteHelper->Attach (ueLteDevs.Get (i), enbLteDevs.Get (0));
//   }

lteHelper->AttachToClosestEnb (ueLteDevs, enbLteDevs);

// for (uint32_t i = 0; i < ueNodes.GetN(); ++i) {
//       Ptr<MobilityModel> mobility = ueNodes.Get(i)->GetObject<MobilityModel>();
//       std::cout<<"UE " << i << " position: " << mobility->GetPosition()<<std::endl;
//   }
//   std::cout<<std::endl;
//   // Print eNB positions
//   for (uint32_t i = 0; i < enbNodes.GetN(); ++i) {
//       Ptr<MobilityModel> mobility = enbNodes.Get(i)->GetObject<MobilityModel>();
//       std::cout<<"eNB " << i << " position: " << mobility->GetPosition()<<std::endl;
//   }
//   std::cout<<std::endl;



for (uint32_t i = 0; i < ueLteDevs.GetN(); i++)
{
Ptr<LteUeNetDevice> ueDevice = ueLteDevs.Get(i)->GetObject<LteUeNetDevice>();
uint16_t cellId = ueDevice->GetRrc()->GetCellId();

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 99);
// Find the eNB device with the same cell ID
for (uint32_t j = 0; j < enbLteDevs.GetN(); j++)
{


Ptr<LteEnbNetDevice> enbDevice = enbLteDevs.Get(j)->GetObject<LteEnbNetDevice>();
if (enbDevice->GetCellId() == cellId)
{   
u_int32_t randomNumber=dis(gen);
cout<<randomNumber<<endl;
NrDevice[ueIpIfaces.GetAddress(i)]=(uint32_t)((randomNumber < 70) ? 0 : 1);
ueToEnbMap[ueIpIfaces.GetAddress(i)] = (uint32_t)(j);
// cout<<ueIpIfaces.GetAddress(i)<<endl;
std::cout << "UE " << i << " attached to eNB " << j << std::endl;
enbStats[j]={0,0,0,0,0,0,0};

break;
}
}
}


// Install and start applications on UEs and remote host
uint16_t dlPort = 10000;
uint16_t ulPort = 20000;

// randomize a bit start times to avoid simulation artifacts
// (e.g., buffer overflows due to packet transmissions happening
// exactly at the same time)
Ptr<UniformRandomVariable> startTimeSeconds = CreateObject<UniformRandomVariable> ();
startTimeSeconds->SetAttribute ("Min", DoubleValue (0));
startTimeSeconds->SetAttribute ("Max", DoubleValue (0.010));

Ptr<UniformRandomVariable> randomVariable = CreateObject<UniformRandomVariable> ();
randomVariable->SetAttribute ("Min", DoubleValue (0.0));
randomVariable->SetAttribute ("Max", DoubleValue (1.0));

for (uint32_t u = 0; u < numberOfUes; ++u)
{


Ptr<Node> ue = ueNodes.Get (u);
// Set the default gateway for the UE
Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ue->GetObject<Ipv4> ());
ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);

//for (uint32_t b = 0; b < numBearersPerUe; ++b)
{

++dlPort;
++ulPort;

double randvalue = randomVariable->GetValue ();
ApplicationContainer clientApps;
ApplicationContainer serverApps;
if (randvalue<0.2){
//voice
  UdpClientHelper dlClient(ueIpIfaces.GetAddress (u), dlPort);
  dlClient.SetAttribute("PacketSize", UintegerValue(60));
  dlClient.SetAttribute("MaxPackets", UintegerValue(1000000)); 
  dlClient.SetAttribute("Interval", TimeValue(MilliSeconds(60))); 
  clientApps.Add(dlClient.Install(remoteHost));

  PacketSinkHelper dlPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), dlPort));
  serverApps.Add(dlPacketSinkHelper.Install(ue));

  // voice
  UdpClientHelper ulClient(remoteHostAddr, ulPort);
  ulClient.SetAttribute("PacketSize", UintegerValue(60)); 
  ulClient.SetAttribute("MaxPackets", UintegerValue(50000000)); 
  ulClient.SetAttribute("Interval", TimeValue(MilliSeconds(60))); 
  clientApps.Add(ulClient.Install(ue));

  PacketSinkHelper ulPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), ulPort));
  serverApps.Add(ulPacketSinkHelper.Install(remoteHost));
}
else if (randvalue <0.5){
  UdpClientHelper dlClient(ueIpIfaces.GetAddress (u), dlPort);
  dlClient.SetAttribute("PacketSize", UintegerValue(1024)); 
  dlClient.SetAttribute("MaxPackets", UintegerValue(500000000)); 
  dlClient.SetAttribute("Interval", TimeValue(MilliSeconds(50))); 
  clientApps.Add(dlClient.Install(remoteHost));

  PacketSinkHelper dlPacketSinkHelper("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), dlPort));
  serverApps.Add(dlPacketSinkHelper.Install(ue));

  // Uplink Traffic (Web Browsing Requests)
  UdpClientHelper ulClient(remoteHostAddr, ulPort);
  ulClient.SetAttribute("PacketSize", UintegerValue(100)); 
  ulClient.SetAttribute("MaxPackets", UintegerValue(500000000)); 
  ulClient.SetAttribute("Interval", TimeValue(MilliSeconds(100))); 
  clientApps.Add(ulClient.Install(ue));

  PacketSinkHelper ulPacketSinkHelper("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), ulPort));
  serverApps.Add(ulPacketSinkHelper.Install(remoteHost));
}
else{
//video
ResourceFactor[ueIpIfaces.GetAddress(u)]=1;
UdpClientHelper dlClientHelper(ueIpIfaces.GetAddress(u), dlPort);
dlClientHelper.SetAttribute("MaxPackets", UintegerValue(0xFFFFFFFF));
dlClientHelper.SetAttribute("PacketSize", UintegerValue(1400));
dlClientHelper.SetAttribute("Interval", TimeValue(MilliSeconds(1000 / 30))); 
clientApps.Add(dlClientHelper.Install(remoteHost));

PacketSinkHelper dlPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), dlPort));
serverApps.Add(dlPacketSinkHelper.Install(ue));
}




Ptr<EpcTft> tft = Create<EpcTft> ();
EpcTft::PacketFilter dlpf;
dlpf.localPortStart = dlPort;
dlpf.localPortEnd = dlPort;
tft->Add (dlpf);
EpcTft::PacketFilter ulpf;
ulpf.remotePortStart = ulPort;
ulpf.remotePortEnd = ulPort;
tft->Add (ulpf);
EpsBearer bearer (EpsBearer::GBR_CONV_VOICE);
lteHelper->ActivateDedicatedEpsBearer (ueLteDevs.Get (u), bearer, tft);

Time startTime = Seconds (startTimeSeconds->GetValue ());
serverApps.Start (startTime);
clientApps.Start (startTime);

} 
}


// Add X2 inteface
// lteHelper->AddX2Interface (enbNodes);
// Time::SetResolution (Time::US);

Simulator::Stop (Seconds (simTime));
// AnimationInterface anim ("lte2.xml");
//anim.EnablePacketMetadata ();
// anim.SetMaxPktsPerTraceFile (100000000000);
// anim.SetMobilityPollInterval(Seconds(1));
//anim.EnablePacketMetadata(true);
// std::string fileNameWithNoExtension = "FlowVSThroughput_";
// std::string graphicsFileName        = fileNameWithNoExtension + ".png";
// std::string plotFileName            = fileNameWithNoExtension + ".plt";
// std::string plotTitle               = "Flow vs Throughput";
// std::string dataTitle               = "Throughput";

// Gnuplot gnuplot (graphicsFileName);
// gnuplot.SetTitle (plotTitle);

// Gnuplot2dDataset dataset;
// dataset.SetTitle (dataTitle);
// dataset.SetStyle (Gnuplot2dDataset::LINES_POINTS);

// //flowMonitor declaration
FlowMonitorHelper fmHelper;
Ptr<FlowMonitor> allMon = fmHelper.InstallAll();
allMon->CheckForLostPackets ();
// call the flow monitor function
ThroughputMonitor(&fmHelper, allMon); 

Simulator::Run ();

// gnuplot.AddDataset (dataset);
// std::ofstream plotFile (plotFileName.c_str());
// gnuplot.GenerateOutput (plotFile);
// plotFile.close ();
Simulator::Destroy ();
return 0;
}