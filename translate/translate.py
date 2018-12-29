import argparse
import json
import copy
import re

PATH_TO_DEFAULT_ORDER = "../sources/defaultOrder.json"

mapForTranslateToString = {
    "HeadYaw" :         "HY",
    "HeadPitch" :       "HP",
    "LShoulderPitch" :  "LSP",
    "LShoulderRoll" :   "LSR",
    "LElbowYaw" :       "LEY",
    "LElbowRoll" :      "LER",
    "LWristYaw" :       "LWY",
    "LHipYawPitch" :    "LHYP",
    "LHipRoll" :        "LHR",
    "LHipPitch" :       "LHP",
    "LKneePitch" :      "LKP",
    "LAnklePitch" :     "LAP",
    "LAnkleRoll" :      "LAR",
    "RHipYawPitch" :    "LHYP",
    "RHipRoll" :        "RHR",
    "RHipPitch" :       "RHP",
    "RKneePitch" :      "RKP",
    "RAnklePitch" :     "RAP",
    "RAnkleRoll" :      "RAR",
    "RShoulderPitch" :  "RSP",
    "RShoulderRoll" :   "RSR",
    "RElbowYaw" :       "REY",
    "RElbowRoll" :      "RER",
    "RWristYaw" :       "RWY"
}

mapForTranslateToInt = {}

def printJson(json, output, name) :
    out   = "%s {\n%s\n}\n"
    param = "\t%s : %s\n"
    params = ""

    for i in json :
        params += param % (i, json[i])

    output.write(out % (name, params))

def toVertex(position, output, name) :
    if output is None:
        output = "translate_" + input
    
    with open(PATH_TO_DEFAULT_ORDER) as f:
        default_list_order = json.load(f)
    
    writeJson = {}

    for i in default_list_order :
        if mapForTranslateToString[i] == None :
            print("WARNING: can not find %s in mapForTranslateToString (probably, usless param)\n" % (i))
            writeJson[i] = 0
            continue

        if mapForTranslateToInt.get(mapForTranslateToString[i]) == None :
            print("WARNING: can not find %s in mapForTranslateToSting (probably, other comant did not fockus on this param)\n" % (mapForTranslateToString[i]))
            writeJson[i] = 0
            continue

        writeJson[i] = position[mapForTranslateToInt[mapForTranslateToString[i]]]

    printJson(writeJson, output, name)

def translate(input, output):
    with open(input) as file:
        positions = []
        numString = 0
        for line in file :
            position  = []
            line = re.sub('\n', '', line)
            split   = line.split(' ')
            for i in split :
                i.strip()
                if (i != '') :
                    position.append(i)
            
            if numString == 0 :
                numPosition = -1
                for i in position :
                    mapForTranslateToInt[i] = numPosition
                    numPosition += 1

            if len(position) > 0 and not('#' in position[0]) and not ('$' in position[0]) :
                positions.append(position)
            numString += 1


        with open(output, 'w', encoding='utf-8') as fileOutput:
            ind = 0
            for position in positions :
                toVertex(position, fileOutput, str(ind))
                ind += 1



if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--input',  action='store', type=str, help='input file',  required=True)
    parser.add_argument('--output', action='store', type=str, help='output file', required=True)
    
    args = parser.parse_args()
    
    translate(args.input, args.output)
