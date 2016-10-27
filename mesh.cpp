#include "mesh.h"
#include <vector>

mesh::mesh(const std::string& fileName){
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    initMesh(model);
}

mesh::mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;

    for(int i = 0; i < numVertices; i++){
        model.positions.push_back(*vertices[i].GetPos());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
    }

    for(int i = 0; i < numIndices; i++){
        model.indices.push_back(indices[i]);
    }

    initMesh(model);

    /*//drawCount = numVertices;
    drawCount = numIndices;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    positions.reserve(numVertices);
    textureCoordinates.reserve(numVertices);

    for(int i = 0; i < numVertices; i++){
        positions.push_back(*vertices[i].GetPos());
        textureCoordinates.push_back(*vertices[i].GetTexCoord());
    }*/
}

void mesh::initMesh(const IndexedModel& model){

    drawCount = model.indices.size();

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

    //Position Coordinates :
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Texture Coordinates :
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

mesh::~mesh()
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vertexArrayObject);
}


void mesh::Draw(){
    glBindVertexArray(vertexArrayObject);
    //glDrawArrays(GL_TRIANGLES, 0, drawCount);
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
}
