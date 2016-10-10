Imports System.Math

Public Class Town

#Region "------------------------------------ fields ------------------------------------"
    Private xCoord As Integer
    Private yCoord As Integer
#End Region

#Region "------------------------------------ properties ------------------------------------"
    Public ReadOnly Property x As Integer
        Get
            Return xCoord
        End Get
    End Property

    Public ReadOnly Property y As Integer
        Get
            Return yCoord
        End Get
    End Property

    Public Property name As String
#End Region
#Region "------------------------------------ initialisation ------------------------------------"
    Sub New(Optional x As Integer = 0, Optional y As Integer = 0, Optional name As String = "noname")
        xCoord = x
        yCoord = y
        Me.name = name
    End Sub

#End Region

    Public Function distance(ByRef s As Town) As Double
        Dim deltaX = Abs(xCoord - s.xCoord)
        Dim deltaY = Abs(yCoord - s.yCoord)
        Return Sqrt(deltaX * deltaX + deltaY * deltaY)
    End Function
End Class
