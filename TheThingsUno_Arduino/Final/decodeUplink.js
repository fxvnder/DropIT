function decodeUplink(input) {
  return {
    data: {
      byte_moistsensor: input.bytes[0],
      byte_dht_hum_int: input.bytes[1],
      byte_dht_hum_deci: input.bytes[2],
      byte_dht_temp_int: input.bytes[3],
      byte_dht_temp_deci: input.bytes[4]
    },
    warnings: [],
    errors: []
  };
}