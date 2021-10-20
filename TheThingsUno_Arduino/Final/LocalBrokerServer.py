#import context 
import paho.mqtt.subscribe as subscribe
import smtplib
from email.message import EmailMessage

def email_alert(subject, body, to):
    msg = EmailMessage()
    msg.set_content(body)
    msg['subject'] = subject
    msg['to'] = to

    user = "xxgamerxpto@gmail.com"
    msg['from'] = user
    password = "uewmwlrqnnksxjay"

    server = smtplib.SMTP("smtp.gmail.com",587)
    server.starttls()
    server.login(user,password)
    server.send_message(msg)

    server.quit()

index = 0
flag = 0
maxhumactivated = 0
while True:
    m = subscribe.simple(topics=['#'], hostname="eu1.cloud.thethings.network", port=1883, auth={'username':"fikadropit",'password':"NNSXS.XAUNAJ73KL6OQMVNMV4JQZYHTHNUBP47Z3MUVBY.N5CUF5SSXDCT6C4YHYR5TG46PBVSINT5EGFOWSWJLNEXP4JCFLAQ"}, msg_count=2)
    for a in m:
        print ("-- LOOP")
        if flag == 0:
            print(a.topic)
        flag = 1
        # .decode("utf-8"), transforms class bytes into class str
        # .split separates the string into an array based on the commas
        bananasplit = a.payload.decode("utf-8").split(",")
        
        # Get the number of each element
        '''
        i = 0
        for element in bananasplit:
            print(i, "=", element)
            i += 1
        print(bananasplit[17])
        '''
        extractedValuestr = ""
        for element in bananasplit:
            if "moistsensor" in element:
                for ch in element:
                    if ch.isdigit():
                        extractedValuestr += ch
        extractedValue = int(extractedValuestr)
        if extractedValue > 130:
            email_sent_str =  ""
            if maxhumactivated == 0:
                email_sent_str =  "Email sent"
                index += 1
                subject = "Mosit Warning! - "
                subject += str(index)

                corpse = "The wetness level is "
                corpse += str(extractedValue)
                corpse += " (0 to 255), it's above 130!"
                email_alert(subject, corpse, "yesheysangpo@gmail.com") # instead of my email ("yesheysangpo@gmail.com"), my number 
            maxhumactivated = 1
            print("moist value: " + extractedValuestr + ", above 130! " + email_sent_str)
        else:
            print("moist value: " + extractedValuestr)
            maxhumactivated = 0

        # DHT
        for element in bananasplit:
            if "dht_temp_int" in element:
                extractedValuestr = ""
                for ch in element:
                    if ch.isdigit():
                        extractedValuestr += ch
                dht_temp_int = int(extractedValuestr)
            if "dht_temp_deci" in element:
                extractedValuestr = ""
                for ch in element:
                    if ch.isdigit():
                        extractedValuestr += ch
                dht_temp_deci = int(extractedValuestr)
            if "dht_hum_int" in element:
                extractedValuestr = ""
                for ch in element:
                    if ch.isdigit():
                        extractedValuestr += ch
                dht_hum_int = int(extractedValuestr)            
            if "dht_hum_deci" in element:
                extractedValuestr = ""
                for ch in element:
                    if ch.isdigit():
                        extractedValuestr += ch
                dht_hum_deci = int(extractedValuestr)                
        dht_temp = dht_temp_int + (dht_temp_deci/100)
        dht_hum = dht_hum_int + (dht_hum_deci/100)

        print("DHT22: ")
        print("Humidity: " + str(dht_hum) + " % \t Temperature: " + str(dht_temp) + " *C") 