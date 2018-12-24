import argparse
import json
import copy
import re

PATH_TO_DEFAULT_ORDER = "../sources/defaultOrder.json"

mapForTranslate = {
    "HeadYaw" :         0,
    "HeadPitch" :       1,
    "LShoulderPitch" :  2,
    "LShoulderRoll" :   3,
    "LElbowYaw" :       4,
    "LElbowRoll" :      5,
    "LWristYaw" :       6,
    "LHipYawPitch" :    8,
    "LHipRoll" :        9,
    "LHipPitch" :       10,
    "LKneePitch" :      11,
    "LAnklePitch" :     12,
    "LAnkleRoll" :      13,
    "RHipYawPitch" :    8,
    "RHipRoll" :        14,
    "RHipPitch" :       15,
    "RKneePitch" :      16,
    "RAnklePitch" :     17,
    "RAnkleRoll" :      18,
    "RShoulderPitch" :  19,
    "RShoulderRoll" :   20,
    "RElbowYaw" :       21,
    "RElbowRoll" :      22,
    "RWristYaw" :       23
}

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
        writeJson[i] = position[mapForTranslate[i]]

    printJson(writeJson, output, name)

def translate(input, output):
    with open(input) as file:
        positions = []
        for line in file :
            position  = []
            line = re.sub('\n', '', line)
            split   = line.split(' ')
            for i in split :
                i.strip()
                if (i != '') :
                    position.append(i)
            
            
            if len(position) > 0 and not('#' in position[0]) and not ('$' in position[0]) :
                positions.append(position)


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
