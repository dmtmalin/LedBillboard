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

    void show();
private:
    explicit BillboardService();
    ~BillboardService();

    MediaWindow *mediaView;
};

#endif // BILLBOARDSERVICE_H
