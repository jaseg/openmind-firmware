#!/usr/bin/env ruby

bp = File.new("/dev/ttyUSB0", "w+")
begin
  bp.syswrite("\nm 5 4 1 1 2 2 1\n(2)\n") #second number: 2 for 125kHz, 4 for 1MHz
  while true
    print bp.gets(sep=']').split(/\(/).map{|s| s.delete(")]")[-2,2].hex.chr}.join
    print "\n"
  end
rescue
  bp.syswrite("#")
  bp.close
end
