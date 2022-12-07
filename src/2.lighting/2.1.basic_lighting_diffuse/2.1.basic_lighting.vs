#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // 我们还需要片段的位置，我们会在世界空间中进行所有的光照计算，因此我们需要一个在世界空间中的顶点位置
    // 通过把顶点位置属性乘以模型矩阵（不是观察和投影矩阵）来把它变换到世界空间坐标
    FragPos = vec3(model * vec4(aPos, 1.0));
    // 首先，法向量只是一个方向向量，不能表达空间中的特定位置。同时，法向量没有齐次坐标（顶点位置中的w分量）。
    // 这意味着，位移不应该影响到法向量。因此，如果我们打算把法向量乘以一个模型矩阵，我们就要从矩阵中移除位移部分，
    // 只选用模型矩阵左上角3×3的矩阵（注意，我们也可以把法向量的w分量设置为0，再乘以4×4矩阵；这同样可以移除位移）。
    // 对于法向量，我们只希望对它实施缩放和旋转变换。
    // 法线矩阵(Normal Matrix) ：逆矩阵(Inverse Matrix)和转置矩阵(Transpose Matrix)
    // Normal = mat3(transpose(inverse(model))) * aNormal;
    //  矩阵求逆是一项对于着色器开销很大的运算，因为它必须在场景中的每一个顶点上进行，所以应该尽可能地避免在着色器中进行求逆运算
    Normal = aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}