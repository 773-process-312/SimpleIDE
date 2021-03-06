''This code example is from Propeller Education Kit Labs: Fundamentals, v1.2.
''A .pdf copy of the book is available from www.parallax.com, and also through
''the Propeller Tool software's Help menu (v1.2.6 or newer).
''
'' TestRcDecay.spin
'' Test RC circuit decay measurements.

CON
   
  _clkmode = xtal1 + pll16x                  ' System clock → 80 MHz
  _xinfreq = 5_000_000

OBJ
   
  pst : "Parallax Serial Terminal"           ' Use with Parallax Serial Terminal to
                                             ' display values 
   
PUB Init

  'Start Parallax Serial Terminal; waits 1 s for you to click Enable button

  pst.Start(115_200)

  ' Configure counter module.

  ctra[30..26] := %01000                     ' Set mode to "POS detector"
  ctra[5..0] := 17                           ' Set APIN to 17 (P17)
  frqa := 1                                  ' Increment phsa by 1 for each clock tick

  main                                       ' Call the Main method

PUB Main | time

'' Repeatedly takes and displays P17 RC decay measurements.

  repeat

     ' Charge RC circuit.

     dira[17] := outa[17] := 1               ' Set pin to output-high
     waitcnt(clkfreq/100_000 + cnt)          ' Wait for circuit to charge
      
     ' Start RC decay measurement.  It's automatic after this...

     phsa~                                   ' Clear the phsa register
     dira[17]~                               ' Pin to input stops charging circuit

     ' Optional - do other things during the measurement.

     pst.Str(String(pst#NL, pst#NL, "Working on other tasks", pst#NL))
     repeat 22
       pst.Char(".")
       waitcnt(clkfreq/60 + cnt)        

     ' Measurement has been ready for a while.  Adjust ticks between phsa~ & dira[17]~.
 
     time := (phsa - 624) #> 0                
     
     ' Display Result                                  

     pst.Str(String(pst#NL, "time = "))
     pst.Dec(time)
     waitcnt(clkfreq/2 + cnt)

