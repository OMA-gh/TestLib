#define RESOURCE_DIR "Resources/"

#include <iostream>

#include <fbx.h>
#include <fbx.hpp>
#include "FBXModel.h"

FBXModel::FBXModel() : Model() {
}

void FBXModel::setIndexInfo() {
    std::string inputfile = RESOURCE_DIR"oma.fbx";

    fbx::FbxLoader* fbx_model = new fbx::FbxLoader();
    int i = 0;
    if (fbx_model->Initialize(inputfile.c_str())) {
        auto it = fbx_model->GetMeshList().begin();
        auto end = fbx_model->GetMeshList().end();
        for (; it != end; it++) {
            printf("name:%s\n", it->nodeName.c_str());
            printf("material name:%s\n", it->materialName.c_str());
            // set vertex list
            {
                auto v_it = it->vertexList.begin();
                auto v_end = it->vertexList.end();
                for (; v_it != v_end; v_it++) {
                    {
                        glm::vec3 push_pos(
                            v_it->position.x,
                            v_it->position.y,
                            v_it->position.z
                        );
                        mPositionArray.push_back(push_pos);
                    }
                    {
                        glm::vec3 push_normal(
                            v_it->normal.x,
                            v_it->normal.y,
                            v_it->normal.z
                        );
                        mNormalArray.push_back(push_normal);
                    }
                    {
                        glm::vec2 push_tex(
                            v_it->uv.x,
                            1-v_it->uv.y
                        );
                        mTexCoordArray.push_back(push_tex);
                    }
                    {
                        glm::vec3 push_color(
                            1.0f,
                            1.0f,
                            1.0f
                        );
                        mColorArray.push_back(push_color);
                    }
                }
            }
            // set index
            {
                auto i_it = it->indexList.begin();
                auto i_end = it->indexList.end();
                for (; i_it != i_end; i_it++) {
                    mIndexArray.push_back(*i_it);
                }
            }
            {
                auto m_it = fbx_model->GetMaterialList().begin();
                auto m_end = fbx_model->GetMaterialList().end();
                for (; m_it != m_end; m_it++) {
                    if (it->materialName == m_it->materialName) {
                        size_t first = m_it->diffuseTextureName.find_last_of('\\');
                        mTextureName = m_it->diffuseTextureName.substr(first, m_it->diffuseTextureName.length() - first);
                    }
                }
            }
        }
    }
}

void FBXModel::update() {
}

