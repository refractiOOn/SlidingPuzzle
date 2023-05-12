#pragma once

#include "Tile.hpp"
#include <QtQmlIntegration>
#include <QAbstractListModel>
#include <random>

namespace game
{

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(size_t boardSize READ boardSize CONSTANT)
    Q_PROPERTY(bool puzzleSolved READ puzzleSolved WRITE setPuzzleSolved NOTIFY puzzleSolvedChanged)

    typedef std::pair<size_t, size_t> position;
    static constexpr size_t defaultBoardSize{4};
public:
    explicit GameModel(const size_t boardSize = defaultBoardSize, QObject *parent = nullptr);

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void currentToInitial();

    Q_INVOKABLE void moveElement(const size_t currentElement);

    size_t boardSize() const;
    bool puzzleSolved() const;

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void puzzleSolvedChanged();

private:
    void shuffle();

    bool isMoveLegal(const size_t currentElementIndex, const size_t blankElementIndex) const;
    position getElementPosition(const size_t elementIndex) const;
    size_t getDistance(const size_t firstElement, const size_t secondElement) const;

    bool isBoardSolvable();
    size_t calculateInversions() const;

    void setPuzzleSolved(bool value);
    bool checkCurrentState() const;

private:
    QVector<Tile> m_initialState{};
    QVector<Tile> m_currentState{};
    QVector<Tile> m_expectedState{};
    size_t m_boardSize{};
    std::mt19937_64 m_generator{};

    bool m_puzzleSolved{};
};

} // namespace game
