import json

class_vertex = 'Vertex'
vector_vertexes = 'vertexes'
vector_edges = 'edges'
emplace_back = 'emplace_back'


def generator(vertex_file="vertex.txt", edge_file="edge.txt", output="automaticinitGeneration.h"):
    with open('sources/defaultPosition.json') as f:
        default_dict_motors = json.load(f)
    with open('sources/defaultOrder.json') as f:
        default_list_order = json.load(f)
    out = open(output, 'w', encoding='utf-8')
    vertex_numbers = dict()
    with open(vertex_file) as file:
        cur_vertex_name = None
        cur_vertex_dict = default_dict_motors
        number = 0
        for line in file:
            line = line.split()
            if cur_vertex_name is None:
                cur_vertex_name = line[0]
                vertex_numbers[cur_vertex_name] = number
                number = number + 1
            elif line[0] != '}':
                cur_vertex_dict[line[0]] = line[2]
            else:
                s =''
                for name in default_list_order:
                    s = s + str(cur_vertex_dict[name]) + ', '
                s = s[:-2]
                out.write(vector_vertexes + '.' + emplace_back + '(' + s + ');\n')
                cur_vertex_name = None
                cur_vertex_dict = default_dict_motors

    out.write('\n')
    with open(edge_file) as file:
        for line in file:
            line = line.split()
            vertex_from = '&' + vector_vertexes + '[' + str(vertex_numbers[line[0]]) + ']'
            vertex_to = '&' + vector_vertexes + '[' + str(vertex_numbers[line[1]]) + ']'
            out.write(vector_edges + '.' + emplace_back + '(' + vertex_from + ', ' + vertex_to + ', ' + line[2] + ');\n')


generator()

