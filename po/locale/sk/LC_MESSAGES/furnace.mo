��             +         �     �  E   �  #   -  #   Q  >   u  "   �  #   �     �          -     F  6   ^     �     �  :   �  )        .     =     U  	   [     e     �     �     �     �  
   �  v   �     :     H  6  d     �    �  1   �	  Q   �	  3   A
  3   u
  A   �
  &   �
  &        9     S  %   m  $   �  =   �     �       0   ,  #   ]     �     �     �  
   �  *   �     �  
   �  
   �  
   	  
     �        �     �  8  �                                                                             
                                 	                                       12xx: Set duty cycle (0 to 8) 20xx: Set channel mode (bit 0: square; bit 1: noise; bit 2: envelope) 21xx: Set noise frequency (0 to 1F) 21xx: Set noise frequency (0 to FF) 22xy: Set envelope mode (x: shape, y: enable for this channel) 23xx: Set envelope period low byte 24xx: Set envelope period high byte 25xx: Envelope slide up 26xx: Envelope slide down 27xx: Set noise AND mask 28xx: Set noise OR mask 29xy: Set auto-envelope (x: numerator; y: denominator) 2Exx: Write to I/O port A 2Fxx: Write to I/O port B Broken output volume - Episode 2 (PLEASE KEEP ME DISABLED) Broken output volume on instrument change Invalid effect Kikai wa mou shindeiru! Noise Sample %d Sega Genesis Extended Channel 3 Sega Genesis/Mega Drive Square 1 Square 2 Square 3 TI SN76489 a square/noise sound chip found on the Sega Master System, ColecoVision, Tandy, TI's own 99/4A and a few other places. file is empty max number of systems is %d these compatibility flags are getting SO damn ridiculous and out of control.
as you may have guessed, this one exists due to yet ANOTHER DefleMask-specific behavior.
please keep this off at all costs, because I will not support it when ROM export comes.
oh, and don't start an argument out of it. Furnace isn't a DefleMask replacement, and no,
I am not trying to make it look like one with all these flags.

oh, and what about the other flags that don't have to do with DefleMask?
those are for .mod import, future FamiTracker import and personal taste!

end of rant too many wavetables! Project-Id-Version: furnace 0.6.5
Last-Translator: Automatically generated
Language-Team: none
Language: sk
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=3; plural=(n==1) ? 0 : (n>=2 && n<=4) ? 1 : 2;
 12xx: Nastav striedu štvorcovej vlny (od 0 do 8) 20xx: Nastav režím kanála (bit 0: štvorec; bit 1: biely šum; bit 2: obálka) 21xx: Nastav frekvenciu bielého šumu (od 0 do 1F) 21xx: Nastav frekvenciu bielého šumu (od 0 do FF) 22xy: Nastav režím obálky (x: tvar, y: zapni pre tento kanál) 23xx: Nastav dolný bajt časa obálky 24xx: Nastav horný bajt časa obálky 25xx: Šmyk obálky nahor 26xx: Šmyk obálky nadol 27xx: Nastav AND masku bielého šumu 28xx: Nastav OR masku bielého šumu 29xy: Nastav automatskú obálku (x: čitateľ; y: činiteľ) 2Exx: Vpíš do I/O port A 2Fxx: Vpíš do I/O port B Pohubený hlas - Časť dva (NECHAJ MA VYPNÚTI) Pohubený hlas na zmene instrumenta Effekt neexistuje Stroj je že mrtev! Noise Snímka %d Sega Mega Drive zo rošírenim 3. kanálom Sega Mega Drive Štvorec 1 Štvorec 2 Štvorec 3 TI SN76489 štvorcoý/nojsový čip, ktorý sa môže najsť vo Sega Master System-e, ColecoVision-eTandy-ne, TI-ovom 99/4A a ešte na niektorých systémach fajl je prazdny Najviac môžete mať %d čipov Tieto kompatibilné nastavenia sú toľko blbé a hlúpe.
Možete uhadnuť, tento problem existuje kvôli EŠTE JEDNEJ DefleMask-ovej chybi.
Prosím vás, nechajte toto vypnúte ako keby vám život závisel od tochto, lebo nebudem podržiavať toto keď príde ROM vývoz.
Tak, nezačínajte spor vôkol tochto. Furnace nie je DefleMask 2.0,aj nechcem,
Aby sa zdalo kvôli tíchto nastaveniach.

No, a čo s týmito nastaveniami čo nemaju nič s DelfeMask-om?
To sú pre .mod učítanie, budúce famitracker učitanie aj pre osobný vkus!

koniec mojích mýšlienok Priveľa wavetablou! 