#ifndef BILLBOARDSERVICE_H
#define BILLBOARDSERVICE_H

#include <singleton.h>

namespace Service {
class BillboardService;
}

class MediaWindow;

class BillboardService
{
public:
    explicit BillboardService();
    ~BillboardService();

    void show();

private:
    MediaWindow *mediaView;
};

typedef Singleton<BillboardService> billboardService;

#endif // BILLBOARDSERVICE_H
