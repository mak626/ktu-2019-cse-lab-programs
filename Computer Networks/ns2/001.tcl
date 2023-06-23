							 #
##################################################################

##################################################################
#	    Setting the Default Parameters			 #
##################################################################

set val(chan)		Channel/WirelessChannel
set val(prop)		Propagation/TwoRayGround
set val(netif)		Phy/WirelessPhy
set val(mac)            Mac/802_11
set val(ifq)		Queue/DropTail/PriQueue
set val(ll)		LL
set val(ant)            Antenna/OmniAntenna
set val(x)		500	
set val(y)		500	
set val(ifqlen)		50		
set val(nn)		7		
set val(stop)		200.0		
set val(rp)             AODV       

##################################################################
#	    Creating New Instance of a Scheduler		 #
##################################################################

set ns_		[new Simulator]

##################################################################
#		Creating Trace files				 #
##################################################################

set tracefd	[open 001.tr w]
$ns_ trace-all $tracefd

##################################################################
#	        Creating NAM Trace files			 #
##################################################################

set namtrace [open 001.nam w]
$ns_ namtrace-all-wireless $namtrace $val(x) $val(y)

set prop	[new $val(prop)]

set topo	[new Topography]
$topo load_flatgrid $val(x) $val(y)

create-god $val(nn)

##################################################################
#		Node Configuration				 #
##################################################################

        $ns_ node-config -adhocRouting $val(rp) \
			 -llType $val(ll) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -ifqLen $val(ifqlen) \
			 -antType $val(ant) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -channelType $val(chan) \
			 -topoInstance $topo \
			 -agentTrace ON \
			 -routerTrace ON \
			 -macTrace ON

##################################################################
#		Creating Nodes					 #
##################################################################

for {set i 0} {$i < $val(nn) } {incr i} {
     set node_($i) [$ns_ node]	
     $node_($i) random-motion 0	
}

##################################################################
#		Initial Positions of Nodes			 #
##################################################################

for {set i 0} {$i < $val(nn)} {incr i} {
	$ns_ initial_node_pos $node_($i) 40
}

##################################################################
#		Topology Design				 	 #
##################################################################

$ns_ at 10.0 "$node_(0) setdest 10.0 10.0 20.0"
$ns_ at 10.0 "$node_(6) setdest 310.0 10.0 20.0"
$ns_ at 10.0 "$node_(1) setdest 10.0 160.0 20.0"
$ns_ at 10.0 "$node_(4) setdest 160.0 160.0 20.0"
$ns_ at 10.0 "$node_(2) setdest 10.0 310.0 20.0"
$ns_ at 10.0 "$node_(5) setdest 310.0 310.0 20.0"
$ns_ at 10.0 "$node_(3) setdest 10.0 460.0 20.0"

##################################################################
#		Generating Traffic				 #
##################################################################

set tcp0 [new Agent/TCP]
set sink0 [new Agent/TCPSink]
$ns_ attach-agent $node_(0) $tcp0
$ns_ attach-agent $node_(5) $sink0
$ns_ connect $tcp0 $sink0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns_ at 30.0 "$ftp0 start" 
$ns_ at 48.0 "$ftp0 stop"

set tcp1 [new Agent/TCP]
set sink1 [new Agent/TCPSink]
$ns_ attach-agent $node_(1) $tcp1
$ns_ attach-agent $node_(5) $sink1
$ns_ connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ns_ at 30.0 "$ftp1 start" 
$ns_ at 48.0 "$ftp1 stop"
$ns_ at 60.0 "$ftp1 start" 
$ns_ at 70.0 "$ftp1 stop"

set tcp2 [new Agent/TCP]
set sink2 [new Agent/TCPSink]
$ns_ attach-agent $node_(2) $tcp2
$ns_ attach-agent $node_(6) $sink2
$ns_ connect $tcp2 $sink2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ns_ at 30.0 "$ftp2 start" 
$ns_ at 48.0 "$ftp2 stop"

set tcp3 [new Agent/TCP]
set sink3 [new Agent/TCPSink]
$ns_ attach-agent $node_(3) $tcp3
$ns_ attach-agent $node_(6) $sink3
$ns_ connect $tcp3 $sink3
set ftp3 [new Application/FTP]
$ftp3 attach-agent $tcp3
$ns_ at 30.0 "$ftp3 start" 
$ns_ at 48.0 "$ftp3 stop"

set tcp4 [new Agent/TCP]
set sink4 [new Agent/TCPSink]
$ns_ attach-agent $node_(4) $tcp4
$ns_ attach-agent $node_(6) $sink4
$ns_ connect $tcp4 $sink4
set ftp4 [new Application/FTP]
$ftp4 attach-agent $tcp4
$ns_ at 30.0 "$ftp4 start" 
$ns_ at 48.0 "$ftp4 stop"

set tcp5 [new Agent/TCP]
set sink5 [new Agent/TCPSink]
$ns_ attach-agent $node_(5) $tcp5
$ns_ attach-agent $node_(6) $sink5
$ns_ connect $tcp5 $sink5
set ftp5 [new Application/FTP]
$ftp5 attach-agent $tcp5
$ns_ at 30.0 "$ftp5 start" 
$ns_ at 48.0 "$ftp5 stop"

set tcp6 [new Agent/TCP]
set sink6 [new Agent/TCPSink]
$ns_ attach-agent $node_(6) $tcp6
$ns_ attach-agent $node_(5) $sink6
$ns_ connect $tcp6 $sink6
set ftp6 [new Application/FTP]
$ftp6 attach-agent $tcp6
$ns_ at 100.0 "$ftp6 produce 3" 

##################################################################
#		Simulation Termination				 #
##################################################################

for {set i 0} {$i < $val(nn) } {incr i} {
    $ns_ at $val(stop) "$node_($i) reset";
}
$ns_ at $val(stop) "puts \"NS EXITING...\" ; $ns_ halt"

puts "Starting Simulation..."

$ns_ run
