function decodeUplink(input) {
    return {
      data: {
        byte_moistsensor: input.bytes[0],
        byte_dhttemperature: input.bytes[1],
        byte_dhthumidity: input.bytes[2]
      },
      warnings: [],
      errors: []
    };
  }