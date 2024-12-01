#ifndef DEV_QUERY_HPP
#define DEV_QUERY_HPP

namespace dev {

    class Query {
    public:
        Query() = default;

        Query(const Query&) = default;
        Query(Query&&) = delete;
        Query& operator=(const Query&) = default;
        Query& operator=(Query&&) = delete;

        virtual ~Query() = default;
    };
}

#endif