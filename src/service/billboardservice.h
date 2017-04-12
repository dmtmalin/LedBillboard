#ifndef BILLBOARDSERVICE_H
#define BILLBOARDSERVICE_H

namespace Service {
class BillboardService;
}

class MediaWindow;

class BillboardService
{
public:
    static BillboardService& Instance() {
        static BillboardService theSingleInstance;
        return theSingleInstance;
    }
    ~BillboardService();

    void show();
private:
    BillboardService();

    MediaWindow *mediaView;
};

#endif // BILLBOARDSERVICE_H
