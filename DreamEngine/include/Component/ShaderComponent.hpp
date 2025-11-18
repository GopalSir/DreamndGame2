#pragma once
#include "../Shader.hpp"
#include <map>
#include <string>

namespace DREAM
{
    // Component to store per-entity shader and its uniforms
    class ShaderComponent : public Component
    {
    public:
        Shader* shader;  // This entity's custom shader
        
        // Store uniform values to be set before rendering
        struct UniformValue {
            enum Type { FLOAT, VEC2, VEC4, INT } type;
            union {
                float f;
                float vec2[2];
                float vec4[4];
                int i;
            } data;
        };
        
        std::map<std::string, UniformValue> uniforms;
        
        ShaderComponent() : shader(nullptr) {}
        
        ShaderComponent(Shader* _shader) : shader(_shader) {}
        
        // Helper methods to set uniforms
        void setUniform(const std::string& name, float value) {
            UniformValue uv;
            uv.type = UniformValue::FLOAT;
            uv.data.f = value;
            uniforms[name] = uv;
        }
        
        void setUniform(const std::string& name, float x, float y) {
            UniformValue uv;
            uv.type = UniformValue::VEC2;
            uv.data.vec2[0] = x;
            uv.data.vec2[1] = y;
            uniforms[name] = uv;
        }
        
        void setUniform(const std::string& name, float x, float y, float z, float w) {
            UniformValue uv;
            uv.type = UniformValue::VEC4;
            uv.data.vec4[0] = x;
            uv.data.vec4[1] = y;
            uv.data.vec4[2] = z;
            uv.data.vec4[3] = w;
            uniforms[name] = uv;
        }
        
        void setUniform(const std::string& name, int value) {
            UniformValue uv;
            uv.type = UniformValue::INT;
            uv.data.i = value;
            uniforms[name] = uv;
        }
        
        // Apply all stored uniforms to the shader
        void applyUniforms() {
            if (!shader) return;
            
            for (auto& pair : uniforms) {
                const std::string& name = pair.first;
                const UniformValue& uv = pair.second;
                
                switch (uv.type) {
                    case UniformValue::FLOAT:
                        shader->setUniform(name, uv.data.f);
                        break;
                    case UniformValue::VEC2:
                        shader->setUniform(name, uv.data.vec2[0], uv.data.vec2[1]);
                        break;
                    case UniformValue::VEC4:
                        shader->setUniform(name, uv.data.vec4[0], uv.data.vec4[1], 
                                         uv.data.vec4[2], uv.data.vec4[3]);
                        break;
                    case UniformValue::INT:
                        shader->setUniform(name, uv.data.i);
                        break;
                }
            }
        }
        
        ~ShaderComponent() {
            // Note: We don't delete shader here - it might be shared
            // Shader lifecycle should be managed separately
        }
    };
}

