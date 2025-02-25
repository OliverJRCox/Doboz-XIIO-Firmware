int finibus(int16_t subject, int16_t basenumber, int16_t topnumber){
  // max
  if (subject > topnumber){
    return topnumber;
  }

  // min
  if (subject < basenumber){
    return basenumber;
  }

  return subject;
}


