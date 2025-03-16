Hi folks, this is an edit of the firmware for the Doboz XIIO - adding a kind of CV mode to the Switch 2 output. 
It's basically raw unfiltered PWM from the capacitative data coming off the MPR121 chip, so please expect weirdness unless you manually filter it outside of this. 
Sadly this is Github, and I can't code for you adding an RC pair to the Switch 2 output. 

The good news is that raw, unfiltered PWM actually sounds great and does weird shit as a modulation source, so consider this a gift in hardware form for anyone who likes creepy noises. 

To access the new modes, just keep scrolling right on the Switch 2 settings, the modes go blue and you're now in a liminal space where your perspective changes. Insert some marketing here. The three modes are just more smoothing, so Blue Mode 1 is raw touch data, 2 is a little bit smoother, 3 is blue whale on a beach being serenaded by Rupert Holmes. 

To be clear, this is a fork of the original Doboz firmware, not the newer Icnagy one with the internal clock. I will try and git merge those two at a later date for One Firmware To Rule Them All, however have a suspicion I may hage to Get Good and learn about hardware timers, which I currently Don't Want To Do. 

Anyway, upload and have some fun. Let me know when you have a bug list together. 
