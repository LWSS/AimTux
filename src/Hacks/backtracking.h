#pragma once

struct CTickRecord;

struct CValidTick {
    explicit operator CTickRecord() const;

    explicit operator bool() const noexcept {
        return m_flSimulationTime > 0.f;
    }

    float m_flPitch = 0.f;
    float m_flYaw = 0.f;
    float m_flSimulationTime = 0.f;
    C_BasePlayer* m_pEntity = nullptr;
};

struct CTickRecord {
    CTickRecord() {}
    CTickRecord(C_BasePlayer* ent) {
        m_flLowerBodyYawTarget = *ent->GetLowerBodyYawTarget();
        m_angEyeAngles = *ent->GetEyeAngles();
        m_flSimulationTime = ent->GetSimulationTime();
        tickcount = 0;
    }

    explicit operator bool() const noexcept {
        return m_flSimulationTime > 0.f;
    }

    bool operator>(const CTickRecord& others) {
        return (m_flSimulationTime > others.m_flSimulationTime);
    }
    bool operator>=(const CTickRecord& others) {
        return (m_flSimulationTime >= others.m_flSimulationTime);
    }
    bool operator<(const CTickRecord& others) {
        return (m_flSimulationTime < others.m_flSimulationTime);
    }
    bool operator<=(const CTickRecord& others) {
        return (m_flSimulationTime <= others.m_flSimulationTime);
    }
    bool operator==(const CTickRecord& others) {
        return (m_flSimulationTime == others.m_flSimulationTime);
    }

    float m_flLowerBodyYawTarget;
    QAngle m_angEyeAngles;
    float m_flSimulationTime;
    CValidTick validtick;
    int tickcount = 0;
};

inline CValidTick::operator CTickRecord() const{
    CTickRecord rec(m_pEntity);
    rec.m_angEyeAngles.x = this->m_flPitch;
    rec.m_angEyeAngles.y = this->m_flYaw;
    rec.m_flSimulationTime = this->m_flSimulationTime;
    return rec;
}
