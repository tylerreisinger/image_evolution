#ifndef MIPMAPCOLLECTION_H_
#define MIPMAPCOLLECTION_H_

#include <memory>
#include <tuple>
#include <vector>

#include "Image.h"

class MipmapCollection {
public:
    explicit MipmapCollection(std::unique_ptr<Image> image);
    ~MipmapCollection();

    MipmapCollection(const MipmapCollection& other) = delete;
    MipmapCollection(MipmapCollection&& other) noexcept = delete;
    MipmapCollection& operator =(const MipmapCollection& other) = delete;
    MipmapCollection& operator =(MipmapCollection&& other) noexcept = delete;

    int full_width() const {return full_image().width();}
    int full_height() const {return full_image().height();}

    std::size_t num_levels() const {return m_mipmap_levels.size();}

    std::tuple<int, int> get_level_dimensions(int level) const;

    const Image& full_image() const {return *m_mipmap_levels[0];}

    const Image& get_image_level(int level) const;

protected:
    void generate_mipmap(std::unique_ptr<Image>&& image);

    static int max_level_for_image(const Image& image);

    std::vector<std::unique_ptr<Image>> m_mipmap_levels;
};

#endif
