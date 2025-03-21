void switchPlates() {

  if (page == settings_page) {
    return;
  }

  for (int i = 0; i < 2; i++) {
    switchPlateRead [i] = bitRead(plates, 2 + i);

    switch (switchPlateBehavior[i]) {

      // momentary
      case momentary_switch:
        if (switchPlateRead[i] != switchPlateLast[i]) {
          switchPlateStatus[i] = switchPlateRead[i];

          doChange = 1;

          if (i == 1 && mode && glideLegato) {
            arpGlide = switchPlateStatus[i];
            if (!arpGlide) { // switch off gliding
              TIMSK1 = 0x0;
              gliding = 0;
              writeDAC(glideStop);
            }
          }
        }
        // momentary glide in auto mode

        break;

      // trigger
      case trigger_switch:
        // trigger ON
        if (switchPlateRead[i] == 1 && switchPlateLast[i] == 0) {
          switchPlateStatus[i] = 1;
          switchPlateTriggerTime[i] = millis();
        }
        // trigger OFF
        if (switchPlateStatus[i] == 1 && millis() - switchPlateTriggerTime[i] >= 20) {
          switchPlateStatus[i] = 0;
          doChange = 1;
        }
        break;

      // latching
      case latching_switch:
        if (switchPlateRead[i] == 1 && switchPlateLast[i] == 0) {
          switchPlateStatus[i] = !switchPlateStatus[i];
          doChange = 1;
        }

        // freeze in auto mode
        if (i == 0 && mode && enableFreeze) {
          if (switchPlateRead[0] == 1 && switchPlateLast[0] == 0) {
            freeze = !freeze;
          }
          switchPlateStatus[0] = freeze;
        }
        break;

        // CV switch mode - addressing this with PWM. If switch is pressed, output CV 
        // directly from that key. If not, look for last key pressed on keyboard.
        case cv_switch:
          Serial.println("A MODE");

          if (switchPlateRead[i] == 1) {
            switch1cv = ((platesFilteredData[11]-filteredDataLowerBound)*filteredDataMultiplier);
            doChange = 1;
          }
          else if (activeNotePlates == 0){
            switch1cv = 255;
            doChange = 1;
          }
          else {
            switch1cv = ((platesFilteredData[activeNote]-filteredDataLowerBound)*filteredDataMultiplier);
            doChange = 1;
          }
        break;


        // CV switch B mode (smoothed A mode)
        case cv_switch_Bmode:
          if (switchPlateRead[i] == 1) {
            smoothedBValue.add((platesFilteredData[11]-filteredDataLowerBound)*filteredDataMultiplier);
            switch1cv = smoothedBValue.get_avg();
            doChange = 1;
          }
          else if (activeNotePlates == 0){
            smoothedBValue.add(255);
            switch1cv = smoothedBValue.get_avg();
            doChange = 1;
          }
          else {
            smoothedBValue.add((platesFilteredData[activeNote]-filteredDataLowerBound)*filteredDataMultiplier);
            switch1cv = smoothedBValue.get_avg();
            doChange = 1;
          }
        break;

         // CV switch C mode (currrently the same as A mode)
        case cv_switch_Cmode:
          if (switchPlateRead[i] == 1) {
            smoothedCValue.add((platesFilteredData[11]-filteredDataLowerBound)*filteredDataMultiplier);
            switch1cv = smoothedCValue.get_avg();
            doChange = 1;
          }
          else if (activeNotePlates == 0){
            smoothedCValue.add(255);
            switch1cv = smoothedCValue.get_avg();
            doChange = 1;
          }
          else {
            smoothedCValue.add((platesFilteredData[activeNote]-filteredDataLowerBound)*filteredDataMultiplier);
            switch1cv = smoothedCValue.get_avg();
            doChange = 1;
          }
        break;


    }

    // refresh LEDs if change happened
    if (switchPlateRead[i] != switchPlateLast[i]) {
      doChange = 1;
    }

    switchPlateLast[i] = switchPlateRead[i];

    // do outputs if change happened
    if (doChange == 1) {
        if (switchPlateStatus[0] == 0) {
          switch0low;
        }

        if (switchPlateStatus[0] == 1) {
          switch0high;
        }
      
      if (switchPlateBehavior[1] <= 2) {
        if (switchPlateStatus[1] == 0) {
          //switch1low;
          switch1cv = 255;
        }
        if (switchPlateStatus[1] == 1) {
          //switch1high;
          switch1cv = 0;

        }
      }
      else {
        //outputCV();
        //Serial.println(activeNote);
      }


    }
  }

}

