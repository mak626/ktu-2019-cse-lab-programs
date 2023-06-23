#create a new simulator object ns

set ns [new Simulator]

# creation of two nodes n0 and n1

set n0 [$ns node]

set n1 [$ns node]

#Open the files for tracing in write mode, if the file already exits, it will be overwritten, else a #new file will be created

set tracefile [open out.tr w]

$ns trace-all $tracefile

#Open the files for network animation

set namfile [open out.nam w]

$ns namtrace-all $namfile

#Create a duplex link between nodes n0 and n1

$ns duplex-link $n0 $n1 2MB 10ms DropTail

#Creates TCP Agent and attach it to node 0

set tcp0 [new Agent/TCP]

$ns attach-agent $n0 $tcp0

#creates TCP Sink Agent and attach that agent to node 1

set tcpsink0 [new Agent/TCPSink]

$ns attach-agent $n1 $tcpsink0

# Set the Traffic for FTP and attach it to TCP Agent

set ftp [new Application/FTP]

$ftp attach-agent $tcp0

#connect the source and the sink

$ns connect $tcp0 $tcpsink0

#Start the traffic at 1.0seconds.

$ns at 1.0 "$ftp start"

#call the finish procedure at 4.0 sec

$ns at 4.0 "finish"

#Procedure finish{}

proc finish {} {

            global ns tracefile namfile

            exec nam out.nam &;  #execute the animation within the procedure

            exit 0

}

#Run the simulation

$ns run
