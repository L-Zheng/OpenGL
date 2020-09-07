//
//  main.cpp
//  testMacOS
//
//  Created by EM on 2020/9/7.
//  Copyright © 2020 EM. All rights reserved.
//

#include <stdio.h>
// 着色管理器
#include "GLShaderManager.h"
#include "GLTools.h"
#include <glut/glut.h>

// 容器
GLBatch triangleBatch;
GLShaderManager shaderManager;

//窗口大小改变回调：设置视口、投影方式
void ChangeSize(int w,int h){
    // x y用于定位视口的左下角位置
    glViewport(0, 0, w, h);
}

//初始配置
void SetupRC()
{
    //设置背景颜色：rgba
    glClearColor(0.0f,1.0f,0.0f,1.0f);
    //初始化着色管理器
    shaderManager.InitializeStockShaders();
    
    //设置三角形顶点数组，三维坐标系x/y/z。
    GLfloat vVerts[] = {
        -0.5f,0.0f,0.0f,
        0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f,
    };
    
    //批次处理:数据传给着色管理器
    // 三角形
    triangleBatch.Begin(GL_TRIANGLES,3);
    /**正方形
     GLfloat vVerts[] = {
             -0.1f,-0.1f,0.0f,
             0.1f,-0.1f,0.0f,
             0.1f,0.1f,0.0f,
             -0.1f,0.1f,0.0f
     };
     triangleBatch.Begin(GL_TRIANGLE_FAN, 4);
     */
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

// 屏幕渲染 or 手动渲染 回调
void RenderScene(void)
{
    /**清除特定的缓冲区
        GL_COLOR_BUFFER_BIT :颜色缓存区：当前激活的用来进行颜色写入缓冲区
        GL_DEPTH_BUFFER_BIT :深度缓存区
        GL_STENCIL_BUFFER_BIT:模板缓冲区
     */
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    //设置颜色：一组浮点数 rgba
    GLfloat vColor[] = {0.0f,0.0f,1.0f,1.0f};
    //传递到存储着色器，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色在屏幕上渲染几何图形
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vColor);
    //提交着色器
    triangleBatch.Draw();
    // 双缓冲区渲染环境：后台渲染，渲染完成交给前台
    //将在后台缓冲区进行渲染，然后在结束时交换到前台
    glutSwapBuffers();
}

// 监听键盘
void SpecialKeys(int key, int x, int y){
    /**上下左右
     修改vVerts中的顶点数据，vVerts[10] = xx;
     
     着色器渲染
     triangleBatch.CopyVertexData3f(vVerts);
     glutPostRedisplay();
     */
    if (key == GLUT_KEY_UP) {
    }
    if (key == GLUT_KEY_DOWN) {
    }
    if (key == GLUT_KEY_LEFT) {
    }
    if (key == GLUT_KEY_RIGHT) {
    }
}

int main(int argc,char* argv[])
{
    /**设置当前工作目录，针对MAC OS X
        Mac OS X中，程序将当前工作文件夹改为应用程序捆绑包中的`/Resource`文件夹
        Windows中不必要，工作目录默认就是与程序可执行执行程序相同的目录
     */
    gltSetWorkingDirectory(argv[0]);
    //初始化GLUT库
    glutInit(&argc, argv);
    /**初始化双缓冲窗口
     GLUT_DOUBLE：双缓冲窗口：绘图命令是在离屏缓存区后台执行的，然后迅速转换成窗口视图
     GLUT_RGBA：RGBA颜色模式
     GLUT_DEPTH：深度测试：将一个深度缓存区分配为显示的一部分
     GLUT_STENCIL：模板缓冲区
     */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    
    //设置窗口大小，标题
    glutInitWindowSize(800,600);
    glutCreateWindow("Test");
    
    //注册回调函数：窗口创建 or 改变大小
    glutReshapeFunc(ChangeSize);
    //注册回调函数：屏幕渲染 or 手动渲染 回调
    glutDisplayFunc(RenderScene);
    //注册回调函数：监听键盘
    glutSpecialFunc(SpecialKeys);
    
    //初始化GLEW库,确保OpenGL API对程序完全可用
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        fprintf(stderr,"glewInit error:%s\n",glewGetErrorString(err));
        return 1;
    }
    //调用SetupRC
    SetupRC();
    //开启运行循环
    glutMainLoop();
    return 0;
}
