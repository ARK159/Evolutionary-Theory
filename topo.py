from ns import ns
nodes=ns.network.NodeContainer()
nodes.Create(4)
mobility = ns.mobility.MobilityHelper()
mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel")
mobility.Install(nodes)
lte_helper = ns.lte.LteHelper()
lte_helper.SetAttribute("PathlossModel", ns.core.StringValue("ns3::FriisPropagationLossModel"))