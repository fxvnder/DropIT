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

def sendNotify():
    print("yay")

while True:
    m = subscribe.simple(topics=['#'], hostname="eu1.cloud.thethings.network", port=1883, auth={'username':"fikadropit",'password':"NNSXS.XAUNAJ73KL6OQMVNMV4JQZYHTHNUBP47Z3MUVBY.N5CUF5SSXDCT6C4YHYR5TG46PBVSINT5EGFOWSWJLNEXP4JCFLAQ"}, msg_count=2)
    index = 0
    for a in m:
        print(a.topic)
        #print("-----------------------------------") #separator

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
            if "decoded_payload" in element:
                # print(element) 
                for ch in element:
                    if ch.isdigit():
                        extractedValuestr += ch
        extractedValue = int(extractedValuestr)
        print(extractedValue)
        if extractedValue > 130:
            index += 1
            subject = "Mosit Warning! - "
            subject += str(index)
            email_alert(subject, "The wetness level is above 130!", "yesheysangpo@gmail.com") # instead of my email ("yesheysangpo@gmail.com"), my number 