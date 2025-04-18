#include "canvas2D/Canvas.hpp"

#include "glad/gl.h"
#include "libtess2/tesselator.h"

#include <glm/gtc/matrix_transform.hpp>

namespace canvas2D{

    namespace OpenGL {

        bool init(const GLADloadfunc l) {
            return gladLoadGL(l);
        }

    }

    Canvas::Canvas() {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void Canvas::clear(const Color & color){
        glClearColor(color.r,color.g,color.b,color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Canvas::resize(const int w, const int h){
        m_size = {w,h};
        glViewport(0,0,w,h);
        m_projection = glm::ortho(0.f,static_cast<float>(w),static_cast<float>(h),0.f);
    }

    void Canvas::scale(const float x, const float y){
        m_transform = glm::scale(m_transform,glm::vec3{x,y,1});
    }

    void Canvas::rotate(const float angle){
        m_transform = glm::rotate(m_transform,angle,glm::vec3{1,0,0});
    }

    void Canvas::translate(const float x, const float y){
        m_transform = glm::translate(m_transform,glm::vec3{x,y,0});
    }

    void Canvas::transform(const float a, const float b, const float c, const float d, const float e, const float f){
        m_transform *= glm::mat4{
            a,b,c,0,
            d,e,f,0,
            0,0,1,0,
            0,0,0,1
        };
    }

    glm::mat4 Canvas::getTransform() const {
        return m_transform;
    }

    void Canvas::setTransform(const float a, const float b, const float c, const float d, const float e, const float f){
        m_transform = glm::mat4{
            a,b,c,0,
            d,e,f,0,
            0,0,1,0,
            0,0,0,1
        };
    }

    void Canvas::setTransform(const glm::mat4& mat){
        m_transform = mat;
    }

    void Canvas::resetTransform(){
        m_transform = glm::mat4{1.f};
    }

    Gradient Canvas::createLinearGradient(double x0, double y0, double x1, double y1){
        //TODO(Canvas::createLinearGradient)
        return {};
    }

    Gradient Canvas::createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1){
        //TODO(Canvas::createRadialGradient)
        return {};
    }

    Gradient Canvas::createConicGradient(double startAngle, double x, double y){
        //TODO(Canvas::createConicGradient);
        return {};
    }

    Pattern  Canvas::createPattern(const Image& image, const std::string& repetition){
        //TODO(Canvas::createPattern);
        return {};
    }

    int asInt(const float f) {
        return static_cast<int>(f);
    }

    void Canvas::clearRect(const float x, const float y, const float w, const float h){
        glEnable(GL_SCISSOR_TEST);
        glScissor((asInt(x)), asInt(m_size.y - y - h), asInt(w), asInt(h));
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);
    }

    void Canvas::fillRect(const float x, const float y, const float w, const float h){
        Path p;
        p.rect(x,y,w,h);
        fill(p);
    }

    void Canvas::strokeRect(const float x, const float y, const float w, const float h){
        Path p;
        p.rect(x,y,w,h);
        stroke(p);
    }

    void Canvas::beginPath(){
        m_path.clear();
    }

    void Canvas::fill(const FillRule fillRule){
        fill(m_path,fillRule);
    }

    void Canvas::fill(const Path& path, const FillRule fillRule){
        auto contours = std::vector<std::vector<glm::vec2>>();
        auto current  = std::vector<glm::vec2>();
        for (const auto item : path.data()) {
            if (item == internal::PATH_END) {
                contours.push_back(current);
                current.clear();
            }else {
                current.push_back(item);
            }
        }

        TESStesselator* tess = tessNewTess(nullptr);
        if (!tess) return;

        for (const auto& contour : contours) {
            if (contour.size() < 3) continue;
            tessAddContour(tess, 2, contour.data(), sizeof(glm::vec2), static_cast<int>(contour.size()));
        }

        if (tessTesselate(tess, fillRule == FillRule::NonZero ? TESS_WINDING_NONZERO : TESS_WINDING_ODD,
            TESS_POLYGONS, 3, 2, nullptr)
        ) {
            const float* verts = tessGetVertices(tess);
            const int* elems = tessGetElements(tess);
            const int nelems = tessGetElementCount(tess);

            glBindVertexArray(m_vao);
            if (nelems * 2 > m_vbo_size) {
                m_vbo_size = nelems * 2;
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferData(GL_ARRAY_BUFFER, static_cast<int>(m_vbo_size * sizeof(glm::vec2)), nullptr, GL_DYNAMIC_DRAW);
            }

            if (nelems * 2 > m_ebo_size) {
                m_ebo_size = nelems * 2;
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int>(m_ebo_size * sizeof(GLuint)), nullptr, GL_DYNAMIC_DRAW);
            }

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<int>(nelems * sizeof(glm::vec2)), verts);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<int>(nelems * sizeof(GLuint)), elems);
            glDrawElements(GL_TRIANGLES, static_cast<int>(m_vbo_size), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);

        }

        tessDeleteTess(tess);
    }

    void Canvas::stroke(){

    }

    void Canvas::stroke(const Path& path){

    }

    void Canvas::clip(FillRule fillRule){

    }

    void Canvas::clip(const Path& path, FillRule fillRule){

    }

    bool Canvas::isPointInPath(float x, float y, FillRule fillRule){
        return false;
    }

    bool Canvas::isPointInPath(const Path& path, float x, float y, FillRule fillRule){
        return false;
    }

    bool Canvas::isPointInStroke(float x, float y){
        return false;
    }

    bool Canvas::isPointInStroke(const Path& path, float x, float y){
        return false;
    }

    void Canvas::fillText(const std::string& text, float x, float y, float maxWidth){

    }

    void Canvas::strokeText(const std::string& text, float x, float y, float maxWidth){

    }

    TextMetrics Canvas::measureText(const std::string& text) {
        return {};
    }

    void Canvas::drawImage(const Image& image, float dx, float dy){

    }

    void Canvas::drawImage(const Image& image, float dx, float dy, float dw, float dh){

    }

    void Canvas::drawImage(const Image& image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh){

    }

    void Canvas::closePath(){
        m_path.closePath();
    }

    void Canvas::moveTo(const float x, const float y){
        m_path.moveTo(x,y);
    }

    void Canvas::lineTo(const float x, const float y){
        m_path.lineTo(x,y);
    }

    void Canvas::quadraticCurveTo(const float cpx, const float cpy, const float x, const float y){
        m_path.quadraticCurveTo(cpx,cpy,x,y);
    }

    void Canvas::bezierCurveTo(const float cp1x, const float cp1y, const float cp2x, const float cp2y, const float x, const float y){
        m_path.bezierCurveTo(cp1x,cp1y,cp2x,cp2y,x,y);
    }

    void Canvas::arcTo(const float x1, const float y1, const float x2, const float y2, const float radius){
        m_path.arcTo(x1,y1,x2,y2,radius);
    }

    void Canvas::rect(const float x, const float y, const float w, const float h){
        m_path.rect(x,y,w,h);
    }

    void Canvas::roundRect(const float x, const float y, const float w, const float h, const std::initializer_list<float>& radii){

    }

    void Canvas::roundRect(const float x, const float y, const float w, const float h, const std::initializer_list<glm::vec2>& radii){

    }

    void Canvas::arc(const float x, const float y, const float radius,
                     const float startAngle, const float endAngle, const bool counterclockwise){
        m_path.arc(x,y,radius,startAngle,endAngle,counterclockwise);
    }

    void Canvas::ellipse(const float x, const float y,
                         const float radiusX, const float radiusY, const float rotation,
                         const float startAngle, const float endAngle, const bool counterclockwise){
        m_path.ellipse(x,y,radiusX,radiusY,rotation,startAngle,endAngle,counterclockwise);
    }

    void Canvas::setLineDash(const std::vector<float>& segments) {
        m_dash = segments;
    }

    std::vector<float> Canvas::getLineDash() const {
        return m_dash;
    }


}
