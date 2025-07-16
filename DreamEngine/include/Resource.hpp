

using glResourceID = unsigned int;

class Resource {
    public:
        Resource();
        glResourceID getID() const;
        virtual void release() = 0;
        virtual ~Resource() = default;
    private:
    protected:
        glResourceID id;
};

